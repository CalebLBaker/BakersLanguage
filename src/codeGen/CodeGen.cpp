#include "CodeGen.h"

#include "lld/Common/Driver.h"
#include "llvm/ADT/Triple.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"


namespace CodeGen {
	llvm::LLVMContext context;
	llvm::Module codeModule("target", context);
	llvm::IRBuilder builder(context);

	void newFunction(std::string_view name) {
		llvm::Type *pVoid = llvm::Type::getVoidTy(context);
		llvm::FunctionType *pFuncType = llvm::FunctionType::get(pVoid, false);
		const char *pName = name.data();
		llvm::Function *pFunc = llvm::Function::Create(
			pFuncType, llvm::Function::ExternalLinkage, pName, &codeModule
		);
		llvm::BasicBlock *pBlock = llvm::BasicBlock::Create(context, "entry", pFunc);
		builder.SetInsertPoint(pBlock);
		builder.CreateRetVoid();
	}

	void createExecutable(std::string_view filename) {

		// Add inline assembly to call main
		codeModule.appendModuleInlineAsm(
			".globl _start\n_start:\ncall main\nmov $60, %rax\nmov $0, %rdi\nsyscall\n"
		);

		llvm::InitializeAllTargetInfos();
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmParsers();
		llvm::InitializeAllAsmPrinters();
		std::string triple = llvm::sys::getDefaultTargetTriple();
		std::string error;
		const llvm::Target *pTarget = llvm::TargetRegistry::lookupTarget(triple, error);

		std::string cpu = "generic";
		std::string features = "";
		llvm::TargetOptions options;
		llvm::Optional<llvm::Reloc::Model> relocationModel;

		std::unique_ptr<llvm::TargetMachine> pTargetMachine(pTarget->createTargetMachine(
			triple, cpu, features, options, relocationModel
		));

		codeModule.setDataLayout(pTargetMachine->createDataLayout());

		std::error_code errorCode;
		llvm::raw_fd_ostream output("tmp.o", errorCode, llvm::sys::fs::OF_None);
		llvm::legacy::PassManager passManager;
		pTargetMachine->addPassesToEmitFile(
			passManager, output, nullptr, llvm::TargetMachine::CGFT_ObjectFile
		);
		passManager.run(codeModule);
		output.flush();

		lld::elf::link({"lld", "tmp.o", "-o", filename.data()}, false);
		remove("tmp.o");
	}
}


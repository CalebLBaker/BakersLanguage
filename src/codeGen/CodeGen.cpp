#include "CodeGen.h"

#include <iostream>

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

	void newFunction(std::string_view name, bool entryPoint) {
		llvm::Type *pVoid = llvm::Type::getVoidTy(context);
		llvm::FunctionType *pFuncType = llvm::FunctionType::get(pVoid, false);
		const char *pName = name.data();
		llvm::Function *pFunc = llvm::Function::Create(
			pFuncType,
			entryPoint ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage,
			pName,
			&codeModule
		);
		llvm::BasicBlock *pBlock = llvm::BasicBlock::Create(context, "entry", pFunc);
		builder.SetInsertPoint(pBlock);
		builder.CreateRetVoid();
	}

	void generateOutput(FileType type, std::string_view filename) {

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

		std::unique_ptr<llvm::TargetMachine> pTargetMachine(pTarget->createTargetMachine(triple, cpu, features, options, relocationModel));

		codeModule.setDataLayout(pTargetMachine->createDataLayout());

		if (type == ASSEMBLY) {
			std::error_code errorCode;
			llvm::raw_fd_ostream output(filename.data(), errorCode, llvm::sys::fs::OF_Text);
			llvm::legacy::PassManager passManager;
			pTargetMachine->addPassesToEmitFile(passManager, output, nullptr, llvm::CGFT_AssemblyFile);
			passManager.run(codeModule);
		}
		else if (type == EXECUTABLE) {
			std::error_code errorCode;
			llvm::raw_fd_ostream output("tmp.o", errorCode, llvm::sys::fs::OF_Text);
			llvm::legacy::PassManager passManager;
			pTargetMachine->addPassesToEmitFile(passManager, output, nullptr, llvm::CGFT_ObjectFile);
			passManager.run(codeModule);
			llvm::raw_os_ostream out(std::cout);
			llvm::raw_os_ostream err(std::cerr);
			auto linkCommand = {"lld", "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2", "/usr/lib64/Scrt1.o", "/usr/lib64/crti.o", "-L/lib", "tmp.o", "-lc", "/usr/lib64/crtn.o" };
			lld::elf::link(linkCommand, false, out, err);
//				"-o", filename.data(),
//				"/usr/lib64/gcc/x86_64-pc-linux-gnu/10.1.0/crtbeginS.o",
//				"-L/usr/lib64/gcc/x86_64-pc-linux-gnu/10.1.0",
//				"-L/usr/lib64",
//				"-L/usr/lib",
//				"-lgcc",
//				"--as-needed",
//				"-lgcc_s",
//				"--no-as-needed",
//				"/usr/lib64/gcc/x86_64-pc-linux-gnu/10.1.0/crtendS.o",
			//lld::elf::link({"lld", "tmp.o", "-o", filename.data()}, false, out, err);
			remove("tmp.o");
		}
	}
}


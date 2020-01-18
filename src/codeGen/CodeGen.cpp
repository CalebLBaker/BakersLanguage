#include "CodeGen.h"

#include "llvm/IR/IRBuilder.h"


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
}


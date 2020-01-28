#ifndef CODEGEN_H
#define CODEGEN_H


#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"


namespace CodeGen {
	extern llvm::LLVMContext context;
	extern llvm::Module codeModule;

	void newFunction(std::string_view name);

	inline void setModuleName(std::string_view name) {
		codeModule.setModuleIdentifier(llvm::StringRef(name.data(), name.size()));
	}

	inline void setSourceFilename(std::string_view name) {
		codeModule.setSourceFileName(llvm::StringRef(name.data(), name.size()));
	}

	void createExecutable(std::string_view filename);

}


#endif


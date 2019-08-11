#include "globalDefines.h"
#include "Program.h"


Program::Program() : SyntaxNode() {
	types.emplace("void", VOID);
	types.emplace("sint8", SINT8);
	types.emplace("sint16", SINT16);
	types.emplace("sint32", SINT32);
	types.emplace("sint64", SINT64);
	types.emplace("uint8", UINT8);
	types.emplace("uint16", UINT16);
	types.emplace("uint32", UINT32);
	types.emplace("uint64", UINT64);
}


Error Program::parse(Scanner *scanner) {
	location = scanner->next_token.location;
	while (scanner->next_token.type != END_OF_FILE) {
		function_list.push_back(FunctionDeclaration());
		Error error = function_list.back().parse(scanner);
		if (!error.ok()) {
			return error;
		}
	}
	return Error();
}


Error Program::doSemanticAnalysis() {
	bool found_main = false;
	for (FunctionDeclaration& i : function_list) {
		Error err = i.analyzeSignature(this);
		if (!err.ok()) {
			return err;
		}
		if (!functions.emplace(i.name, &i).second) {
			return Error(DUPLICATE_FUNCTION_SIGNATURE, i.location);
		}
		if (i.name == "main")
		{
			found_main = true;
		}
	}
	return found_main ? Error() : Error(MAIN_NOT_FOUND, Location());
}


Error Program::genCode() {
	for (FunctionDeclaration& i : function_list) {
		code.emplace_back(Function());
		Error err = i.genCode(&(code.back()));
		if (!err.ok()) {
			return err;
		}
	}
	return Error();
}


Error Program::printCode(FILE *file) const {
#ifdef TARGET_X64
 #ifdef TARGET_UNIX
	fprintf(file, "GLOBAL _start\n_start:\n\tmov rdi, [rsp]\n\tlea rsi, [rsp+8]\n\tcall main\n\tmov rax, 60\n\txor rdi, rdi\n\tsyscall\n");
 #endif
#endif
	for (const Function& i : code) {
		Error err = i.printCode(file);
		if (!err.ok()) {
			return err;
		}
	}
	return Error();
}


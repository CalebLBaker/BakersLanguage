
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
		functions.push_back(FunctionDeclaration());
		Error error = functions.back().parse(scanner);
		if (!error.ok()) {
			return error;
		}
	}
	return Error();
}


Error Program::doSemanticAnalysis() {
	for (FunctionDeclaration& i : functions) {
		Error err = i.analyzeSignature(this);
		if (!err.ok()) {
			return err;
		}
	}
	return Error();
}


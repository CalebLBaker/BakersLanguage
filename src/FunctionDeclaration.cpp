#include "FunctionDeclaration.h"


Error FunctionDeclaration::parse(Scanner *scanner) {
	location = scanner->next_token.location;
	Error error = return_type.parse(scanner);
	if (!error.ok()) {
		return error;
	}
	Token next_token = scanner->getNextToken();
	if (next_token.type == IDENTIFIER) {
		name = std::move(*(next_token.value));
	}
	else {
		return Error(EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	error = parameters.parse(scanner);
	if (!error.ok()) {
		return error;
	}
	return body.parse(scanner);
}


Error FunctionDeclaration::analyzeSignature(const Program *program) {
	return return_type.doSemanticAnalysis(program);
}


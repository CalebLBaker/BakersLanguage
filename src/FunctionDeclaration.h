#ifndef FUNCTION_DECLARATION_H
#define FUNCTION_DECLARATION_H

#include "Declaration.h"
#include "Type.h"
#include "ParameterList.h"
#include "CompoundStatement.h"

// FunctionDeclaration represents a Function in the Abstract Syntax Tree
class FunctionDeclaration : public Declaration {

public:

	// return_type is the type that the function returns
	Type return_type;

	// name is the name of the function
	std::string name;

	// parameters is the list of parameters taken by the function
	ParameterList parameters;

	// body is the body of the function
	CompoundStatement body;

	Error parse(Scanner *scanner) {
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

};

#endif

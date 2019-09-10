#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(Scope *s, Namespace *n) : Statement(s, n), type(nullptr), name("") {}

Error VariableDeclaration::parse(Scanner *scanner) {
	type = std::make_unique<Type>(scope, context);
	Error error = type->parse(scanner);
	if (!error.ok()) {
		return error;
	}
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER)
	{
		name = std::move(*next_token.value.strValue);
	}
	else
	{
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	return scanner->matchNextToken(Token::SEMICOLON);
}


Error VariableDeclaration::doSemanticAnalysis() {
	return type->doSemanticAnalysis();
}


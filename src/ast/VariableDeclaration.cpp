#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(Scope *s, Namespace *n) : Statement(s, n), type(nullptr), name("") {}

Error VariableDeclaration::parse(Scanner *scanner) {
	type = std::make_unique<Type>(scope, context);
	TRY(type->parse(scanner));
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER)
	{
		name = std::move(*next_token.value.str_value);
	}
	else
	{
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	next_token = scanner->getNextToken();
	switch (next_token.type) {
		case Token::SEMICOLON: {
			return Error();
		}
		case Token::ASSIGNMENT_OPERATOR: {
			initializer = std::make_unique<Expression>(scope, context);
			TRY(initializer->parse(scanner));
			return scanner->matchNextToken(Token::SEMICOLON);
		}
		default: {
			std::string message = "Unexpected token " + next_token.toString() + ". Expected \";\"";
			return Error(Error::UNEXPECTED_TOKEN, std::move(next_token.location), std::move(message));
		}
	}
}


Error VariableDeclaration::doSemanticAnalysis() {
	TRY(type->doSemanticAnalysis());
	TRY(initializer->doSemanticAnalysis());
	const TypeDefinition *lvalue_type = type->definition;
	const TypeDefinition *rvalue_type = initializer->type;
	if (lvalue_type->stripConst() == rvalue_type->stripConst()) {
		return Error();
	}
	std::string message = "Cannot assign value of type " + rvalue_type->toString();
	message += " to a variable of type " + lvalue_type->toString();
	return Error(Error::TYPE_MISMATCH, location, message);
}


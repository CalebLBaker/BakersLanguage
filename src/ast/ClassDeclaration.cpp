#include "ClassDeclaration.h"


ClassDeclaration::ClassDeclaration(Scope *s, Namespace *n) : TypeDefinition(), SyntaxNode(s, n),
                                                             name() {}


ClassDeclaration::ClassDeclaration(ClassDeclaration&& old) : SyntaxNode(std::move(old)), name(std::move(old.name)) {}


Error ClassDeclaration::parse(Scanner *scanner) {
	Error result = scanner->matchNextToken(Token::CLASS);
	if (!result.ok()) {
		return result;
	}
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.strValue));
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	result = scanner->matchNextToken(Token::LEFT_BRACE);
	if (!result.ok()) {
		return result;
	}
	return scanner->matchNextToken(Token::RIGHT_BRACE);
}


#include "ClassDeclaration.h"


ClassDeclaration::ClassDeclaration(Scope *s, Namespace *n) : TypeDefinition(), SyntaxNode(s, n),
                                                             name() {}


ClassDeclaration::ClassDeclaration(ClassDeclaration&& old) : SyntaxNode(std::move(old)), name(std::move(old.name)) {}


Error ClassDeclaration::parse(Scanner *scanner) {
	TRY(scanner->matchNextToken(Token::CLASS));
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.str_value));
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	TRY(scanner->matchNextToken(Token::LEFT_BRACE));
	return scanner->matchNextToken(Token::RIGHT_BRACE);
}


std::string ClassDeclaration::toString() const {
	return name;
}


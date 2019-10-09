#include "ParameterList.h"


ParameterList::ParameterList(Scope *s) : SyntaxNode(s) {}


Error ParameterList::parse(Scanner *scanner) {
	Error result = scanner->matchNextToken(Token::LEFT_PAREN);
	location = result.location;
	if (!result.ok()) {
		return result;
	}
	result = scanner->matchNextToken(Token::RIGHT_PAREN);
	return result;
}


Error ParameterList::doSemanticAnalysis() {
	return Error();
}


#include "ParameterList.h"


ParameterList::ParameterList(Scope *pScope) : SyntaxNode(pScope) {}


Error ParameterList::parse(Scanner *pScanner) {
	location = pScanner->next_token.location;
	TRY(pScanner->matchNextToken(Token::LEFT_PAREN));
	return pScanner->matchNextToken(Token::RIGHT_PAREN);
}


Error ParameterList::doSemanticAnalysis() {
	return Error();
}


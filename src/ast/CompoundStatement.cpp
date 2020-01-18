#include "CompoundStatement.h"


CompoundStatement::CompoundStatement(Scope *pScope) : Statement(pScope) {}


Error CompoundStatement::parse(Scanner *pScanner) {
	TRY(pScanner->matchNextToken(Token::LEFT_BRACE));
	return pScanner->matchNextToken(Token::RIGHT_BRACE);
}


Error CompoundStatement::doSemanticAnalysis() {
	return Error();
}


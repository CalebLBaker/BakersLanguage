#include "VariableExpression.h"


VariableExpression::VariableExpression(Scope *pScope) : Expression(pScope) {} 


Error VariableExpression::parse(Scanner *pScanner) {
	Token nextToken = pScanner->getNextToken();
	if (nextToken.type != Token::IDENTIFIER) {
		return Error(Error::UNEXPECTED_TOKEN, nextToken.location);
	}
	mName = std::move(*nextToken.value.str_value);
	location = std::move(nextToken.location);
	return Error();
}


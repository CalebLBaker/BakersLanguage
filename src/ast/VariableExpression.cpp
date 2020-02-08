#include "VariableExpression.h"

#include "Scope.h"


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


Error VariableExpression::doSemanticAnalysis() {
	mpDeclaration = scope->getVariable(mName);
	if (mpDeclaration == nullptr) {
		return Error(Error::UNDECLARED_VARIABLE, location);
	}
	mpType = mpDeclaration->getType();
	return Error();
}


const Type* VariableExpression::getTypeValue() {
	return mpDeclaration->getTypeValue();
}


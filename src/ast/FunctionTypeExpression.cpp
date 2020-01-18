#include "FunctionTypeExpression.h"

#include "FunctionType.h"


FunctionTypeExpression::FunctionTypeExpression(Scope *pScope) : Expression(pScope), mParameters(pScope) {}


Error FunctionTypeExpression::parse(Scanner *pScanner) {
	location = pScanner->next_token.location;
	TRY(pScanner->matchNextToken(Token::FUNC));
	TRY(mParameters.parse(pScanner));

	if (pScanner->next_token.type == Token::RETURN_SPECIFIER) {
		pScanner->matchNextToken(Token::RETURN_SPECIFIER);
		return NewExpression(pScanner, scope, &mpReturnType);
	}

	return Error();
}


Error FunctionTypeExpression::doSemanticAnalysis() {
	TRY(mParameters.doSemanticAnalysis());
	if (mpReturnType != nullptr) {
		TRY(mpReturnType->doSemanticAnalysis());
		if (mpReturnType->getType() != Type::TYPE) {
			return Error(Error::NON_TYPE_EXPRESSION, mpReturnType->location, "Function return type must be a type");
		}
	}
	mpType = Type::TYPE;
	mpValue = Type::findType(FunctionType(mParameters, mpReturnType.get()));
	return Error();
}


const Type* FunctionTypeExpression::getTypeValue() {
	return mpValue;
}


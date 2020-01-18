#ifndef FUNCTIONTYPEEXPRESSION_H
#define FUNCTIONTYPEEXPRESSION_H


#include "Expression.h"
#include "ParameterList.h"


class FunctionTypeExpression : public Expression {
public:
	FunctionTypeExpression(Scope *pScope);
	virtual Error parse(Scanner *pScanner);
	virtual Error doSemanticAnalysis();
	virtual const Type* getTypeValue();
private:
	ParameterList mParameters;
	std::unique_ptr<Expression> mpReturnType;
	const Type *mpValue;
};


#endif


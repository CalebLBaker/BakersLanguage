#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H


#include "Declaration.h"
#include "Expression.h"


class VariableExpression : public Expression {
public:
	VariableExpression(Scope *pScope);
	virtual Error parse (Scanner *pScanner);
	virtual Error doSemanticAnalysis();
	virtual const Type* getTypeValue();
private:
	const Declaration *mpDeclaration;
	std::string mName;
};


#endif


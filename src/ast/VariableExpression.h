#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H


#include "Expression.h"


class VariableExpression : public Expression {
public:
	VariableExpression(Scope *pScope);
	virtual Error parse (Scanner *pScanner);
private:
	std::string mName;
};


#endif


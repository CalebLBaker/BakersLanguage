#ifndef INTEGERLITERAL_H
#define INTEGERLITERAL_H


#include "Expression.h"


class IntegerLiteral : public Expression {
public:
	inline IntegerLiteral(Scope *pOwningScope) : Expression(pOwningScope) {
		mpType = Type::INT;
	}
	virtual Error parse(Scanner *pScanner);
	virtual Error doSemanticAnalysis();
	virtual const Type* getTypeValue();
private:
	long long mValue;
};


#endif


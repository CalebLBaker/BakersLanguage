#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H


#include "Expression.h"
#include "ParameterList.h"


class FunctionType : public Type {
public:
	FunctionType(const ParameterList& parameters, const Expression *pReturnType);
	FunctionType(FunctionType&& old);
protected:
	virtual const Type* moveToHeap();
	virtual size_t hash() const;
	virtual bool equal(const Type& rhs) const;
};


#endif


#ifndef STATEMENT_H
#define STATEMENT_H


#include "SyntaxNode.h"

#include "Error.h"


class Statement : public SyntaxNode {
public:
	Statement(Scope *pScope);
	virtual ~Statement();
	virtual Error doSemanticAnalysis() = 0;
};


#endif


#ifndef STATEMENT_H
#define STATEMENT_H


#include "SyntaxNode.h"


class Statement : public SyntaxNode {
public:
	Statement(Scope *pScope);
};


#endif


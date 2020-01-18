#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H


#include "Error.h"
#include "SyntaxNode.h"
#include "scan/Scanner.h"


class ParameterList : SyntaxNode {
public:
	ParameterList(Scope *pScope);
	Error parse(Scanner *pScanner);
	Error doSemanticAnalysis();
};


#endif


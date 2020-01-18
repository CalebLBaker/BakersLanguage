#ifndef INITIALIZER_H
#define INITIALIZER_H


#include "CompoundStatement.h"
#include "Error.h"
#include "scan/Scanner.h"


class Initializer : SyntaxNode {
public:
	Initializer(Scope *pScope);
	~Initializer();
	Error parse(Scanner *pScanner);
	Error doSemanticAnalysis();
	bool isExpression() const;
private:
	CompoundStatement *mpData;
};


#endif


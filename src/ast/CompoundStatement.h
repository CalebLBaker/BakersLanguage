#ifndef COMPOUND_STATEMENT_H
#define COMPOUND_STATEMENT_H


#include "Error.h"
#include "Statement.h"
#include "scan/Scanner.h"


class CompoundStatement : public Statement {
public:
	CompoundStatement(Scope *pScope);
	Error parse(Scanner *pScanner);
	Error doSemanticAnalysis();
};


#endif


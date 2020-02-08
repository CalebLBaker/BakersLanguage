#ifndef COMPOUND_STATEMENT_H
#define COMPOUND_STATEMENT_H


#include <memory>
#include <vector>

#include "Error.h"
#include "Scope.h"
#include "Statement.h"
#include "scan/Scanner.h"


class CompoundStatement : public Statement {
public:
	CompoundStatement(Scope *pScope);
	Error parse(Scanner *pScanner);
	Error doSemanticAnalysis();
private:
	std::vector<std::unique_ptr<Statement>> mStatements;
	Scope mCompoundStatementScope;
};


#endif


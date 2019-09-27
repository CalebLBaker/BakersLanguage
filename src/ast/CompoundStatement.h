#ifndef COMPOUND_STATEMENT_H
#define COMPOUND_STATEMENT_H

#include <vector>
#include <unordered_map>

#include "Scope.h"
#include "VariableDeclaration.h"
#include "scan/Scanner.h"
#include "codeGen/BasicBlock.h"

// CompoundStatement represents a compound statement
class CompoundStatement : public Statement {

public:

	// Default constructor
	CompoundStatement(Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	CompoundStatement(CompoundStatement&& old);

	/**
	 * parse populates the CompoundStatement by parsing Tokens from a Scanner
	 */
	Error parse(Scanner *scanner);

	/**
	 * doSemanticAnalysis performs semantic analysis on the function
	 * returns: an error object indicating any semantic errors that may have occurred
	 */
	Error doSemanticAnalysis();

	/**
	 * genCode generates intermediate low level code for the function
	 * param blocks: the basic blocks of the function containing this compound statement
	 * returns: an error object indicating any errors that may have occurred
	 */
	Error codeGen(std::vector<BasicBlock> *blocks) const;

private:
	std::vector<std::unique_ptr<Statement>> statements;
	std::unordered_map<std::string, VariableDeclaration*> variables;
	Scope local_scope;
};

#endif

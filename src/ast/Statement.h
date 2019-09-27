#ifndef STATEMENT_H
#define STATEMENT_H

#include "scan/Scanner.h"
#include "SyntaxNode.h"
#include "codeGen/BasicBlock.h"

// Statement represents a statement in the abstract syntax tree
class Statement : public SyntaxNode {
public:

	// Default constructor
	Statement(Scope *s = nullptr, Namespace *n = nullptr);

	virtual Error parse(Scanner *scanner) = 0;

	/**
	 * doSemanticAnalysis performs semantic analysis on the function
	 * returns: an error object indicating any semantic errors that may have occurred
	 */
	virtual Error doSemanticAnalysis() = 0;

	/**
	 * codeGen generates low level code for the statement
	 * param blocks: the list of basic blocks in the containing function
	 * returns: an error object indicating any errors that might have occurred
	 */
	virtual Error codeGen(std::vector<BasicBlock> *blocks) const = 0;

};

#endif

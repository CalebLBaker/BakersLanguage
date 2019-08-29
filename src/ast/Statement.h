#ifndef STATEMENT_H
#define STATEMENT_H

#include "scan/Scanner.h"
#include "SyntaxNode.h"

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

};

#endif

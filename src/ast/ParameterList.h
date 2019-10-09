#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

#include "SyntaxNode.h"
#include "scan/Scanner.h"

// Parameter list represents the list of parameters taken by a function.
class ParameterList : SyntaxNode {

public:

	// Default constructor
	ParameterList(Scope *s = nullptr);

	/**
	 * parse populates the ParameterList by parsing Tokens from a Scanner
	 */
	Error parse(Scanner *scanner);

	/**
	 * doSemanticAnalysis performs semantic analysis on the function
	 * returns: an error object indicating any semantic errors that may have occurred
	 */
	Error doSemanticAnalysis();

};

#endif

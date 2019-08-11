#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

#include "SyntaxNode.h"
#include "scan/Scanner.h"

// Parameter list represents the list of parameters taken by a function.
class ParameterList : SyntaxNode {

public:
	/**
	 * parse populates the ParameterList by parsing Tokens from a Scanner
	 */
	Error parse(Scanner *scanner);

};

#endif

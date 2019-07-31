#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

#include "SyntaxNode.h"
#include "Scanner.h"

// Parameter list represents the list of parameters taken by a function.
class ParameterList : SyntaxNode {

public:
	/**
	 * parse populates the ParameterList by parsing Tokens from a Scanner
	 */
	Error parse(Scanner *scanner) {
		Error result = scanner->matchNextToken(LEFT_PAREN);
		location = result.location;
		if (!result.ok()) {
			return result;
		}
		result = scanner->matchNextToken(RIGHT_PAREN);
		return result;
	}
};

#endif

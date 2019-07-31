#ifndef COMPOUND_STATEMENT_H
#define COMPOUND_STATEMENT_H

#include "SyntaxNode.h"
#include "Scanner.h"

// CompoundStatement represents a compound statement
class CompoundStatement : SyntaxNode {

public:
	/**
	 * parse populates the CompoundStatement by parsing Tokens from a Scanner
	 */
	Error parse(Scanner *scanner) {
		Error result = scanner->matchNextToken(LEFT_BRACE);
		location = result.location;
		if (!result.ok()) {
			return result;
		}
		result = scanner->matchNextToken(RIGHT_BRACE);
		return result;
	}
};

#endif

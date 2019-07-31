#ifndef COMPOUND_STATEMENT_H
#define COMPOUND_STATEMENT_H

#include "SyntaxNode.h"
#include "scan/Scanner.h"

// CompoundStatement represents a compound statement
class CompoundStatement : SyntaxNode {

public:
	/**
	 * parse populates the CompoundStatement by parsing Tokens from a Scanner
	 */
	Error parse(Scanner *scanner);

};

#endif

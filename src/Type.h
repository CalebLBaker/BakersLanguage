#ifndef TYPE_H
#define TYPE_H

#include "SyntaxNode.h"
#include "Scanner.h"

// Type represents a data type
class Type : SyntaxNode {

public:

	// name is the name of the type
	std::string name;

	/**
	 * parse populates the Type object by parsing Tokens from a Scanner
	 * param scanner: the scanner to parse tokens from
	 * returns:       an Error object indicating what, if anything, went wrong
	 */
	Error parse(Scanner *scanner) {
		Token next_token = scanner->getNextToken();
		location = next_token.location;
		if (next_token.type == IDENTIFIER) {
			name = std::move(*(next_token.value));
			return Error();
		}
		else {
			return Error(EXPECTED_IDENTIFIER, std::move(next_token.location));
		}
	}
	
};

#endif

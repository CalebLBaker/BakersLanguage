#ifndef DECLARATION_H
#define DECLARATION_H

#include "SyntaxNode.h"
#include "scan/Scanner.h"

// Declaration represents a Declaration in the Abstract Syntax Tree
class Declaration : public SyntaxNode {

public:

	// Default constructor
	Declaration(Scope *s = nullptr, Namespace *n = nullptr);

	/**
	 * parse populates the Declaration by parsing tokens from a scanner
	 * param scanner: the scanner to parse tokens from
	 * returns:       an Error object indicating the success status of the parse operation
	 */
	virtual Error parse(Scanner *scanner) = 0;
};

#endif

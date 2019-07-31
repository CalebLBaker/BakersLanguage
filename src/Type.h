#ifndef TYPE_H
#define TYPE_H

#include "SyntaxNode.h"
#include "Scanner.h"
#include "TypeDefinition.h"

class Program;

// Type represents a reference to a data type
class Type : SyntaxNode {

public:

	// name is the name of the type
	std::string name;

	// definition is a pointer to the definition for the type
	const TypeDefinition *definition;

	/**
	 * parse populates the Type object by parsing Tokens from a Scanner
	 * param scanner: the scanner to parse tokens from
	 * returns:       an Error object indicating what, if anything, went wrong
	 */
	Error parse(Scanner *scanner); 

	/**
	 * doSemanticAnalysis matches the type with the corresponding TypeDefinition
	 * param program: the program that the type is in
	 * returns: an error object indicating whether a definition was successfully found
	 */
	Error doSemanticAnalysis(const Program *program);
	
};

#endif

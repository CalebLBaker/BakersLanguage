#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <unordered_map>
#include "FunctionDeclaration.h"
#include "TypeDefinition.h"

// Program is the root node of an abstract syntax tree
class Program : SyntaxNode {

public:

	// functions is a list of all functions in the global namespace
	std::vector<FunctionDeclaration> functions;

	// types maps type names to type definitions for types declared in the global namespace
	std::unordered_map<std::string, TypeDefinition> types;

	// Program constructs a Program object that includes the type definitions for built-in types
	Program();

	/**
	 * parse parses the program
	 * param scanner: the scanner to parse tokens from
	 * returns:       an error object indicating any syntax error that may have occurred
	 */
	Error parse(Scanner *scanner);

	/**
	 * doSemanticAnalysis performs semantic analysis on the program
	 * returns: an error object indicating any semantic errors that may have occurred
	 */
	Error doSemanticAnalysis();

};

#endif

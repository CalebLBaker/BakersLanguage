#ifndef PROGRAM_H
#define PROGRAM_H

#include <unordered_set>

#include "FunctionDeclaration.h"
#include "codeGen/Function.h"
#include "Namespace.h"
#include "Constant.h"
#include "Slice.h"

// Program is the root node of an abstract syntax tree
class Program : public SyntaxNode {

public:

	// Program constructs a Program object that includes the type definitions for built-in types
	Program();

	// Move constructor
	Program(Program&& old);

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

	/**
	 * genCode generates intermediate low level code for the program
	 * returns: an error object indicating any errors that may have occurred
	 */
	Error genCode();

	/**
	 * printCode prints the assembly to a file
	 * param file: the file to print to
	 * returns: an error object indicating any errors that may have occurred
	 */
	Error printCode(FILE *file) const;

private:
	// function_list is a list of all functions in the global namespace
	std::vector<FunctionDeclaration> function_list;

	// code contains the intermediate low level code for all the functions in the program
	std::vector<Function> code;

	FunctionDeclaration *main;

};

extern std::unordered_set<std::string> string_literals;

#endif

#ifndef PROGRAM_H
#define PROGRAM_H

#include "FunctionDeclaration.h"
#include "codeGen/Function.h"
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
	Error printCode(FILE *file);

	/**
	 * getNextSequenceNumber returns the next unused sequence number (used for generating unique
	 * assemble labels). It is guarenteed to never return the same number twice in one program
	 * execution
	 * returns: the next unused sequence number
	 */
	static size_t getNextSequenceNumber();

	static int64_t getNewRegister();

	/**
	 * addStringLiteral adds a string literal to the set of used string literals if it is not
	 * already there.
	 * param str: the string literal to add
	 */
	static void addStringLiteral(const std::string& str);

	/**
	 * getLabel for string literal retrieves the assembly label that will refer to the string
	 * literal
	 * param value: the string literal to retrieve the label for
	 * returns:     the label that refers to value
	 */
	static std::string getLabel(const std::string& value);

private:
	// function_list is a list of all functions in the global namespace
	std::vector<FunctionDeclaration> function_list;

	// code contains the intermediate low level code for all the functions in the program
	std::vector<Function> code;

	FunctionDeclaration *main;

	static size_t next_sequence_number;

	static int64_t next_register_number;

	static std::unordered_map<std::string, size_t> string_literals;

	static bool isEscapeSequence(char c);

};

#endif

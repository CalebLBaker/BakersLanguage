#ifndef FUNCTION_DECLARATION_H
#define FUNCTION_DECLARATION_H

#include "Declaration.h"
#include "Type.h"
#include "ParameterList.h"
#include "CompoundStatement.h"
#include "codeGen/Function.h"

// FunctionDeclaration represents a Function in the Abstract Syntax Tree
class FunctionDeclaration : public Declaration {

public:

	// name is the name of the function
	std::string name;

	// Default constructor
	FunctionDeclaration(Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	FunctionDeclaration(FunctionDeclaration&& old);

	Error parse(Scanner *scanner);

	/**
	 * analyzeSignature checks for semantic errors in the function signature and connects Types
	 * in the signature with their definitions
	 * param program: the program that the function is in
	 * returns: an error object indicating any semantic errors in the function signature
	 */
	Error analyzeSignature();

	/**
	 * doSemanticAnalysis performs semantic analysis on the function
	 * returns: an error object indicating any semantic errors that may have occurred
	 */
	Error doSemanticAnalysis();

	/**
	 * genCode generates intermediate low level code for the function
	 * param low_level_func: the low level function code object to write to
	 * returns: an error object indicating any errors that may have occurred
	 */
	Error genCode(Function *low_level_func);

private:

	// return_type is the type that the function returns
	std::unique_ptr<Type> return_type;

	// parameters is the list of parameters taken by the function
	ParameterList parameters;

	// body is the body of the function
	CompoundStatement body;

};

#endif

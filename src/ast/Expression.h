#ifndef EXPRESSION_H
#define EXPRESSION_H


#include "Error.h"
#include "scan/Scanner.h"
#include "SyntaxNode.h"
#include "TypeDefinition.h"


class Expression : public SyntaxNode {
	public:

		// The type of the resulting value of the expression
		const TypeDefinition *type;

		// Default constructor
		Expression(Scope *s = nullptr, Namespace *n = nullptr);

		/**
		 * parse parses the Expression from a scanner
		 * param scanner: the scanner to parse from
		 * returns: an error object indicating any syntax errors that occurred in parsing
		 */
		Error parse(Scanner *scanner);

		/**
		 * doSemanticAnalysis analayzes the expression for semantic errors and annotates it with
		 * type information
		 * returns: an error object indicating any semantic errors in the expression
		 */
		Error doSemanticAnalysis();

	private:

		std::string str_value;
		bool is_var;
};


#endif


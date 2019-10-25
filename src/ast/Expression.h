#ifndef EXPRESSION_H
#define EXPRESSION_H


#include "Error.h"
#include "SyntaxNode.h"
#include "TypeDefinition.h"
#include "codeGen/BasicBlock.h"
#include "scan/Scanner.h"


class Expression : public SyntaxNode {
	public:

		// The type of the resulting value of the expression
		const TypeDefinition *type;

		// Name of the variable or value of the string literal
		std::string str_value;

		// Indicates whether the expression is is a variable or just a literal
		bool is_var;

		// Default constructor
		Expression(Scope *s = nullptr);

		// Look ahead constructor
		Expression(Scope *s, Token&& look_ahead);

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

		Error codeGen(std::vector<BasicBlock> *blocks) const;

	private:
		
		Token first_token;

};


#endif


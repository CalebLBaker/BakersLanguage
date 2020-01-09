#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

#include "Error.h"
#include "SyntaxNode.h"
#include "TypeDefinition.h"
#include "codeGen/BasicBlock.h"
#include "scan/Scanner.h"

class VariableDeclaration;


class Expression : public SyntaxNode {
	public:

		Expression(Scope *s);

		static Expression* NewExpression(Scope *s, const Token& look_ahead);

		static Error parseExpression(Scope *scope, Scanner *scanner, std::unique_ptr<Expression> *expr);

		virtual const TypeDefinition* getType() = 0;

		/**
		 * parse parses the Expression from a scanner
		 * param scanner: the scanner to parse from
		 * returns: an error object indicating any syntax errors that occurred in parsing
		 */
		virtual Error parse(Scanner *scanner, Token&& look_ahead) = 0;

		/**
		 * doSemanticAnalysis analayzes the expression for semantic errors and annotates it with
		 * type information
		 * returns: an error object indicating any semantic errors in the expression
		 */
		virtual Error doSemanticAnalysis() = 0;

		virtual Error codeGen(std::vector<BasicBlock> *blocks, const VariableDeclaration *var = nullptr) const = 0;

};


#endif


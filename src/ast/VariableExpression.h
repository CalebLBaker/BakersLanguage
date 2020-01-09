#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H


#include "Expression.h"


class VariableExpression : public Expression {
	public:

		VariableExpression(Scope *s);

		virtual const TypeDefinition *getType();

		virtual Error parse(Scanner *scanner, Token&& look_ahead);

		virtual Error doSemanticAnalysis();

		virtual Error codeGen(std::vector<BasicBlock> *blocks, const VariableDeclaration *var) const;

	private:
		const VariableDeclaration *var;
		std::string name;
};


#endif


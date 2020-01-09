#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H


#include "Expression.h"


class LiteralExpression : public Expression {
	public:
		LiteralExpression(Scope *s);

		virtual const TypeDefinition *getType();

		virtual Error parse(Scanner *scanner, Token&& look_ahead);

		virtual Error doSemanticAnalysis();

		virtual Error codeGen(std::vector<BasicBlock> *blocks, const VariableDeclaration *var) const;
	private:
		std::string str_value;
};


#endif


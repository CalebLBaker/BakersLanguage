#ifndef SYSCALL_EXPRESSION_H
#define SYSCALL_EXPRESSION_H


#include "Expression.h"


class SyscallExpression : public Expression {
	public:
		SyscallExpression(Scope *s);

		virtual const TypeDefinition *getType();

		virtual Error parse(Scanner *scanner, Token&& look_ahead);

		virtual Error doSemanticAnalysis();

		virtual Error codeGen(std::vector<BasicBlock> *blocks, const VariableDeclaration *var) const;
	private:
		std::vector<std::unique_ptr<Expression>> parameters;
};


#endif


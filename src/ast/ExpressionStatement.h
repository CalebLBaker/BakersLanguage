#ifndef EXPRESSION_STATEMENT_H
#define EXPRESSION_STATEMENT_H


#include "Expression.h"
#include "Statement.h"


class ExpressionStatement : public Statement {

	public:

		/**
		 * Default constructor
		 * param s: the owning scope
		 */
		ExpressionStatement(Scope *s);

		/** look-ahead constructor constructs an Expression Statement with a look-ahead token
		 * param s:          the owning scope
		 * param look_ahead: first token to be consumed in parsing before the scanner is consulted
		 */
		ExpressionStatement(Scope *s, Token&& look_ahead);

		Error parse(Scanner *scanner);
		Error doSemanticAnalysis();
		Error codeGen(std::vector<BasicBlock> *blocks) const;
	
	private:

		Expression expr;
};


#endif


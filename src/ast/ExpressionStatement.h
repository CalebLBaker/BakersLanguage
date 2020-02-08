#ifndef EXPRESSIONSTATEMENT_H
#define EXPRESSIONSTATEMENT_H


#include "Expression.h"
#include "Statement.h"


class ExpressionStatement : public Statement {
public:
	inline ExpressionStatement(Scope *pScope) : Statement(pScope) {}

	inline ExpressionStatement(std::unique_ptr<Expression>&& pExpr) :
		Statement(pExpr->scope), mpExpression(std::move(pExpr))
	{}

	inline Error parse(Scanner *pScanner) {
		TRY(Expression::NewExpression(pScanner, scope, &mpExpression));
		return pScanner->matchNextToken(Token::SEMICOLON);
	}

	virtual Error doSemanticAnalysis();
private:
	std::unique_ptr<Expression> mpExpression;
};


#endif


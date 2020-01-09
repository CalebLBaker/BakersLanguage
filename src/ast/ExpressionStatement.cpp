#include "ExpressionStatement.h"


ExpressionStatement::ExpressionStatement(Scope *s, Token&& look_ahead) : Statement(s), expr(Expression::NewExpression(s, std::move(look_ahead))) {}


ExpressionStatement::ExpressionStatement(Scope *s) : Statement(s) {}


Error ExpressionStatement::parse(Scanner *scanner) {
	return Expression::parseExpression(scope, scanner, &expr);
}


Error ExpressionStatement::doSemanticAnalysis() {
	return expr->doSemanticAnalysis();
}


Error ExpressionStatement::codeGen(std::vector<BasicBlock> *blocks) const {
	return expr->codeGen(blocks);
}


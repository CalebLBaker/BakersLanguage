#include "ExpressionStatement.h"


ExpressionStatement::ExpressionStatement(Scope *s, Token&& look_ahead) : Statement(s), expr(s, std::move(look_ahead)) {}


ExpressionStatement::ExpressionStatement(Scope *s) : Statement(s), expr(s) {}


Error ExpressionStatement::parse(Scanner *scanner) {
	return expr.parse(scanner);
}


Error ExpressionStatement::doSemanticAnalysis() {
	return expr.doSemanticAnalysis();
}


Error ExpressionStatement::codeGen(std::vector<BasicBlock> *blocks) const {
	return expr.codeGen(blocks);
}


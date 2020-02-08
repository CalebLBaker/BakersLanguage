#include "ExpressionStatement.h"


Error ExpressionStatement::doSemanticAnalysis() {
	return mpExpression->doSemanticAnalysis();
}


#include "Initializer.h"


Initializer::Initializer(Scope *pScope) : SyntaxNode(pScope) {}


Initializer::~Initializer() {
	if (mpData != nullptr) {
		delete mpData;
	}
}


Error Initializer::parse(Scanner *pScanner) {
	mpData = new CompoundStatement(scope);
	return mpData->parse(pScanner);
}


Error Initializer::doSemanticAnalysis() {
	if (mpData == nullptr) {
		return Error();
	}
	return mpData->doSemanticAnalysis();
}


bool Initializer::isExpression() const {
	return false;
}


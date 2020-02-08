#include "Declaration.h"

#include "CompoundStatement.h"
#include "Scope.h"
#include "codeGen/CodeGen.h"


Declaration::Declaration(Scope *pScope) : Statement(pScope), mpType(nullptr), mpValue(nullptr) {}


Error Declaration::parse(Scanner *pScanner) {
	if (mpTypeExpression == nullptr) {
		TRY(Expression::NewExpression(pScanner, scope, &mpTypeExpression));
	}

	Token nextToken = pScanner->getNextToken();
	if (nextToken.type == Token::IDENTIFIER) {
		mName = std::move(*(nextToken.value.str_value));
		TRY(scope->addVariable(this));
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(nextToken.location));
	}
	if (pScanner->next_token.type == Token::LEFT_BRACE) {
		mpInitializer.reset(new Initializer(scope));
		return mpInitializer->parse(pScanner);
	}
	else {
		return pScanner->matchNextToken(Token::SEMICOLON);
	}
}


std::string_view Declaration::getName() const {
	return mName;
}


Error Declaration::doSemanticAnalysis() {
	TRY(mpTypeExpression->doSemanticAnalysis());
	if (mpTypeExpression->getType() != Type::TYPE) {
		return Error(Error::NON_TYPE_EXPRESSION, mpTypeExpression->location, "Type expression evaluates to a non-type value.\n");
	}
	mpType = mpTypeExpression->getTypeValue();
	if (mpInitializer != nullptr) {
		TRY(mpInitializer->doSemanticAnalysis());
		switch (mpType->getCategory()) {
			case Type::TC_DATA: {
				if (!mpInitializer->isExpression()) {
					return Error(Error::BAD_INITIALIZER, mpTypeExpression->location, "Compound statement initializer not allowed for data variables.\n");
				}
			}
			default: {}
		}
	}
	return Error();
}


Error Declaration::genCode() {
	if (mpTypeExpression->getTypeValue()->getCategory() == Type::TC_FUNCTION) {
		CodeGen::newFunction(mName);
		return Error();
	}
	else {
		return Error(
		   Error::NOT_YET_IMPLEMENTED, mpTypeExpression->location,
		   "Feature not implemented yet"
		);
	}
}


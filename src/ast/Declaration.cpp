#include "Declaration.h"

#include "CompoundStatement.h"
#include "Scope.h"
#include "codeGen/CodeGen.h"


Declaration::Declaration(Scope *pScope) : Statement(pScope) {}


Error Declaration::parse(Scanner *pScanner) {
	TRY(Expression::NewExpression(pScanner, scope, &mpType));

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
		return Error();
	}
}


std::string_view Declaration::getName() const {
	return mName;
}


Error Declaration::doSemanticAnalysis() {
	TRY(mpType->doSemanticAnalysis());
	if (mpType->getType() != Type::TYPE) {
		return Error(Error::NON_TYPE_EXPRESSION, mpType->location, "Type expression evaluates to a non-type value.");
	}
	if (mpInitializer != nullptr) {
		TRY(mpInitializer->doSemanticAnalysis());
		switch (mpType->getTypeValue()->getCategory()) {
			case Type::TC_DATA: {
				if (!mpInitializer->isExpression()) {
					return Error(Error::BAD_INITIALIZER, mpType->location, "Compound statement initializer not allowed for data variables.");
				}
			}
			default: {}
		}
	}
	return Error();
}


Error Declaration::genCode() {
	if (mpType->getTypeValue()->getCategory() == Type::TC_FUNCTION) {
		CodeGen::newFunction(mName);
		return Error();
	}
	else {
		return Error(
		   Error::NOT_YET_IMPLEMENTED, mpType->location,
		   "Feature not implemented yet"
		);
	}
}


#include "Declaration.h"

#include "CompoundStatement.h"
#include "Scope.h"
#include "codeGen/CodeGen.h"


Declaration::Declaration(Scope *pScope) :
	Statement(pScope),
	mpType(nullptr),
	mpValue(nullptr),
	mInitiailizerType(NONE),
	entryPoint(false)
{}


Error Declaration::parse(Scanner *pScanner) {
	if (mpTypeExpression == nullptr) {
		bool entryFunction = pScanner->next_token.type == Token::ENTRY;
		if (entryFunction) {
			pScanner->getNextToken();
		}
		TRY(Expression::NewExpression(pScanner, scope, &mpTypeExpression));
		entryPoint = entryFunction;
	}

	Token nextToken = pScanner->getNextToken();
	if (nextToken.type == Token::IDENTIFIER) {
		mName = std::move(*(nextToken.value.str_value));
		TRY(scope->addVariable(this));
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(nextToken.location));
	}
	Token::TokenType nextTokenType = pScanner->next_token.type;
	if (nextTokenType == Token::LEFT_BRACE) {
		mInitiailizerType = STATEMENT;
		mpInitializer.reset(new CompoundStatement(scope));
		return mpInitializer->parse(pScanner);
	}
	else {
		if (nextTokenType == Token::ASSIGNMENT_OPERATOR) {
			mInitiailizerType = EXPRESSION;
			pScanner->getNextToken();
			TRY(Expression::NewExpression(pScanner, scope, (std::unique_ptr<Expression>*)&mpInitializer));
		}
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
	if (entryPoint && !mpType->mCategory) {
		return Error(Error::NON_FUNCTION_ENTRY, mpTypeExpression->location, "Entry point \"" + mName +"\" is not a function.\n");
	}
	if (mpInitializer != nullptr) {
		TRY(mpInitializer->doSemanticAnalysis());
		switch (mpType->getCategory()) {
			case Type::TC_DATA: {
				if (mInitiailizerType == STATEMENT) {
					return Error(Error::BAD_INITIALIZER, mpTypeExpression->location, "Compound statement initializer not allowed for data variables.\n");
				}
				else if (mInitiailizerType == EXPRESSION) {
					const Expression *pInitializer = (const Expression*)mpInitializer.get();
					if (!mpType->canImplicitCast(pInitializer->getType())) {
						return Error(Error::TYPE_MISMATCH, mpTypeExpression->location, "Initializer is not of the same type as the variable being initialized\n");
					}
				}
			}
			default: {}
		}
	}
	return Error();
}


Error Declaration::genCode() {
	if (mpTypeExpression->getTypeValue()->getCategory() == Type::TC_FUNCTION) {
		CodeGen::newFunction(mName, entryPoint);
		return Error();
	}
	else {
		return Error(
		   Error::NOT_YET_IMPLEMENTED, mpTypeExpression->location,
		   "Feature not implemented yet\n"
		);
	}
}


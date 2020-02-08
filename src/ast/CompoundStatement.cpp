#include "CompoundStatement.h"

#include "Declaration.h"
#include "ExpressionStatement.h"


CompoundStatement::CompoundStatement(Scope *pScope) : Statement(pScope), mCompoundStatementScope(pScope) {}


Error CompoundStatement::parse(Scanner *pScanner) {
	TRY(pScanner->matchNextToken(Token::LEFT_BRACE));
	Token::TokenType next = pScanner->next_token.type;
	while (next != Token::RIGHT_BRACE) {
		if (Expression::inFirstSet(next)) {
			std::unique_ptr<Expression> pExpression;
			TRY(Expression::NewExpression(pScanner, &mCompoundStatementScope, &pExpression));
			switch (pScanner->next_token.type) {
				case Token::SEMICOLON: {
					pScanner->getNextToken();
					auto pStatement = new ExpressionStatement(std::move(pExpression));
					mStatements.emplace_back(pStatement);
					break;
				}
				case Token::IDENTIFIER: {
					Declaration *pStatement = new Declaration(std::move(pExpression));
					TRY(pStatement->parse(pScanner));
					mStatements.emplace_back(pStatement);
					break;
				}
				default: {
					Location *pLocation = &pScanner->next_token.location;
					return Error(Error::UNEXPECTED_TOKEN, std::move(*pLocation));
				}
			}
		}
		else if (next == Token::LEFT_BRACE) {
			auto pCompoundStatement = new CompoundStatement(&mCompoundStatementScope);
			TRY(pCompoundStatement->parse(pScanner));
			mStatements.emplace_back(pCompoundStatement);
		}
		else {
			return Error(Error::UNEXPECTED_TOKEN, std::move(pScanner->next_token.location));
		}
		next = pScanner->next_token.type;
	}
	pScanner->getNextToken();
	return Error();
}


Error CompoundStatement::doSemanticAnalysis() {
	for (std::unique_ptr<Statement>& pStatement : mStatements) {
		TRY(pStatement->doSemanticAnalysis());
	}
	return Error();
}


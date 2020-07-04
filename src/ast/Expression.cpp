#include "Expression.h"

#include "FunctionTypeExpression.h"
#include "IntegerLiteral.h"
#include "VariableExpression.h"


Error Expression::NewExpression(Scanner *pScanner, Scope *pScope, std::unique_ptr<Expression> *pOut) {
	Token::TokenType type = pScanner->next_token.type;
	switch (type) {
		case Token::IDENTIFIER: {
			pOut->reset(new VariableExpression(pScope));
			break;
		}
		case Token::FUNC: {
			pOut->reset(new FunctionTypeExpression(pScope));
			break;
		}
		case Token::INTEGER: {
			pOut->reset(new IntegerLiteral(pScope));
			break;
		}
		default: {
			return Error(Error::UNEXPECTED_TOKEN, pScanner->next_token.location);
		}
	}
	return (*pOut)->parse(pScanner);
}


Expression::Expression(Scope *pScope) : SyntaxNode(pScope) {}


const Type* Expression::getType() const {
	return mpType;
}


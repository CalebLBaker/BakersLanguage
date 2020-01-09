#include "Expression.h"

#include "LiteralExpression.h"
#include "SyscallExpression.h"
#include "VariableExpression.h"


Expression::Expression(Scope *s) : SyntaxNode(s) {}


Expression* Expression::NewExpression(Scope *s, const Token& look_ahead) {
	switch (look_ahead.type) {
		case Token::IDENTIFIER: {
			return new VariableExpression(s);
		}
		case Token::STRING_LITERAL: {
			return new LiteralExpression(s);
		}
		case Token::SYSCALL: {
			return new SyscallExpression(s);
		}
		default: {
			return nullptr;
		}
	}
}


Error Expression::parseExpression(Scope *s, Scanner *scanner, std::unique_ptr<Expression> *expr) {
	Token first_token = scanner->getNextToken();
	expr->reset(NewExpression(s, first_token));
	if (*expr == nullptr) {
		return Error(Error::UNEXPECTED_TOKEN, first_token.location);
	}
	return (*expr)->parse(scanner, std::move(first_token));
}


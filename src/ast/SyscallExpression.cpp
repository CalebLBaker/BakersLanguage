#include "SyscallExpression.h"

#include "Scope.h"


SyscallExpression::SyscallExpression(Scope *s) : Expression(s) {}


const TypeDefinition* SyscallExpression::getType() {
	return INT;
}


Error SyscallExpression::parse(Scanner *scanner, Token&& look_ahead) {
	location = std::move(look_ahead.location);
	TRY(scanner->matchNextToken(Token::LEFT_PAREN));
	Token next = scanner->getNextToken();
	if (next.type == Token::RIGHT_PAREN) {
		return Error();
	}
	Expression *param = NewExpression(scope, next);
	if (param == nullptr) {
		return Error(Error::UNEXPECTED_TOKEN, std::move(next.location));
	}
	param->parse(scanner, std::move(next));
	for (next = scanner->getNextToken(); next.type != Token::RIGHT_PAREN; next = scanner->getNextToken()) {
		if (next.type != Token::COMMA) {
			return Error(Error::UNEXPECTED_TOKEN, std::move(next.location));
		}
		parameters.push_back(nullptr);
		TRY(Expression::parseExpression(scope, scanner, &parameters.back()));
	}
	return Error();
}


Error SyscallExpression::doSemanticAnalysis() {
	for (auto& i : parameters) {
		TRY(i->doSemanticAnalysis());
	}
	return Error();
}


Error SyscallExpression::codeGen(std::vector<BasicBlock> *, const VariableDeclaration *) const {
	throw std::exception();
	return Error();
}



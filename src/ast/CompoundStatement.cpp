#include "CompoundStatement.h"


Error CompoundStatement::parse(Scanner *scanner) {
	Error result = scanner->matchNextToken(Token::LEFT_BRACE);
	location = result.location;
	if (!result.ok()) {
		return result;
	}
	result = scanner->matchNextToken(Token::RIGHT_BRACE);
	return result;
}


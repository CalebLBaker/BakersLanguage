#include "CompoundStatement.h"


Error CompoundStatement::parse(Scanner *scanner) {
	Error result = scanner->matchNextToken(LEFT_BRACE);
	location = result.location;
	if (!result.ok()) {
		return result;
	}
	result = scanner->matchNextToken(RIGHT_BRACE);
	return result;
}


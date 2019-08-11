#include "ParameterList.h"

Error ParameterList::parse(Scanner *scanner) {
	Error result = scanner->matchNextToken(LEFT_PAREN);
	location = result.location;
	if (!result.ok()) {
		return result;
	}
	result = scanner->matchNextToken(RIGHT_PAREN);
	return result;
}


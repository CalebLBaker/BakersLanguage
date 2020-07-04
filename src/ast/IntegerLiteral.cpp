#include "IntegerLiteral.h"


Error IntegerLiteral::parse(Scanner *pScanner) {
	Token nextToken = pScanner->getNextToken();
	if (nextToken.type == Token::INTEGER) {
		location = std::move(nextToken.location);
		mValue = nextToken.value.int_value;
		return Error();
	}
	else {
		return Error(Error::UNEXPECTED_TOKEN, std::move(nextToken.location));
	}
}


Error IntegerLiteral::doSemanticAnalysis() {
	return Error();
}


const Type* IntegerLiteral::getTypeValue() {
	return nullptr;
}


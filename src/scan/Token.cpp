#include "Token.h"


Token::Token(TokenType t, const Location *loc) : type(t), location(loc) {
	value.intValue = 0;
}


Token::Token(const Location *loc, std::string&& val) : type(IDENTIFIER), location(loc) {
	value.strValue = new std::string(std::move(val));
}


Token::Token(const Location *loc, int64_t val) : type(INTEGER), location(loc) {
	value.intValue = val;
}


Token::Token(const Token& token) : type(token.type), location(token.location) {
	if (type == IDENTIFIER) {
		if (token.value.strValue != nullptr) {
			value.strValue = new std::string(*token.value.strValue);
		}
		else {
			value.strValue = nullptr;
		}
	}
	else {
		value.intValue = token.value.intValue;
	}
}


Token::Token(Token&& token) : type(token.type), location(std::move(token.location)) {
	value.intValue = token.value.intValue;
	token.type = ERROR;
	token.value.strValue = nullptr;
}


Token::~Token() {
	if (type == IDENTIFIER) {
		delete value.strValue;
	}
}


void Token::setStringValue(const std::string& val) {
	if (value.strValue == nullptr) {
		value.strValue = new std::string;
	}
	*value.strValue = val;
	type = IDENTIFIER;
}


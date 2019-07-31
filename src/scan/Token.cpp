#include "Token.h"


Token::Token(TokenType t, const Location *loc, std::string&& val) : type(t), location(loc),
   value(new std::string(std::move(val))) {}


Token::Token(const Token& token) : type(token.type), location(token.location) {
	if (token.value != nullptr) {
		value.reset(new std::string(*(token.value)));
	}
}


Token::Token(Token&& token) : type(token.type), location(std::move(token.location)),
					          value(std::move(token.value)) { }


void Token::setValue(const std::string& val) {
	if (value == nullptr) {
		value.reset(new std::string);
	}
	*value = val;
}


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


Token& Token::operator=(Token&& rhs) {
	type = rhs.type;
	location = std::move(rhs.location);
	value.intValue = rhs.value.intValue;
	rhs.type = ERROR;
	rhs.value.strValue = nullptr;
	return *this;
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


std::string Token::toString() const {
	switch (type) {
		case IDENTIFIER: {
			return *value.strValue;
		}
		case INTEGER: {
			return std::to_string(value.intValue);
		}
		default: {
			return tokenTypeToString(type);
		}
	}
}


std::string Token::tokenTypeToString(Token::TokenType type) {
	switch (type) {
		case LEFT_PAREN: {
			return "(";
		}
		case RIGHT_PAREN: {
			return ")";
		}
		case LEFT_BRACE: {
			return "{";
		}
		case RIGHT_BRACE: {
			return "}";
		}
		case LEFT_BRACKET: {
			return "[";
		}
		case RIGHT_BRACKET: {
			return "]";
		}
		case END_OF_FILE: {
			return "EOF";
		}
		case RETURN: {
			return "return";
		}
		case SEMICOLON: {
			return ";";
		}
		case CLASS: {
			return "class";
		}
		case FUNC: {
			return "func";
		}
		case RETURN_SPECIFIER: {
			return "=>";
		}
		case CONST: {
			return "#";
		}
		case ASSIGNMENT_OPERATOR: {
			return "=";
		}
		case IDENTIFIER: {
			return "identifier";
		}
		case INTEGER: {
			return "integer";
		}
		case STRING_LITERAL: {
			return "string";
		}
		default: {
			return "Scanner Error";
		}
	}
}


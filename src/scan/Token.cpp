#include "Token.h"


Token::Token(TokenType t, const Location *loc) : type(t), location(loc) {
	value.int_value = 0;
}


Token::Token(const Location *loc, std::string&& val) : type(IDENTIFIER), location(loc) {
	value.str_value = new std::string(std::move(val));
}


Token::Token(const Location *loc, int64_t val) : type(INTEGER), location(loc) {
	value.int_value = val;
}


Token::Token(const Token& token) : type(token.type), location(token.location) {
	if (type == IDENTIFIER || type == STRING_LITERAL) {
		if (token.value.str_value != nullptr) {
			value.str_value = new std::string(*token.value.str_value);
		}
		else {
			value.str_value = nullptr;
		}
	}
	else {
		value.int_value = token.value.int_value;
	}
}


Token::Token(Token&& token) : type(token.type), location(std::move(token.location)) {
	value.int_value = token.value.int_value;
	token.type = ERROR;
	token.value.str_value = nullptr;
}


Token& Token::operator=(Token&& rhs) {
	type = rhs.type;
	location = std::move(rhs.location);
	value.int_value = rhs.value.int_value;
	rhs.type = ERROR;
	rhs.value.str_value = nullptr;
	return *this;
}


Token::~Token() {
	if (type == IDENTIFIER || type == STRING_LITERAL) {
		delete value.str_value;
	}
}


void Token::setType(Token::TokenType new_type) {
	bool had_string = type == IDENTIFIER || type == STRING_LITERAL;
	bool have_string = new_type == IDENTIFIER || new_type == STRING_LITERAL;
	if (have_string && !had_string) {
		value.str_value = new std::string;
	}
	if (had_string && !have_string) {
		delete value.str_value;
	}
	type = new_type;
}


void Token::setStringValue(const std::string& val) {
	if (value.str_value == nullptr) {
		value.str_value = new std::string;
	}
	*value.str_value = val;
	if (type != STRING_LITERAL) {
		type = IDENTIFIER;
	}
}


std::string Token::toString() const {
	switch (type) {
		case IDENTIFIER: {
			return *value.str_value;
		}
		case INTEGER: {
			return std::to_string(value.int_value);
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
		case SYSCALL: {
			return "SYSCALL";
		}
		case COMMA: {
			return ",";
		}
		case DOT: {
			return ".";
		}
		case ADD: {
			return "+";
		}
		case SUBTRACT: {
			return "-";
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


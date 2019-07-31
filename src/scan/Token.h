#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include "Location.h"

// TokenType is an enumeration used to identify different types of symbols.
enum TokenType {
	IDENTIFIER,
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACE,
	RIGHT_BRACE,
	END_OF_FILE,
	ERROR
};

// Token is a struct used to represent symbols from the input file.
struct Token {

	// location is the location of the symbol.
	Location location;

	// value is used to  store the value of an identifier.
	std::unique_ptr<std::string> value;

	// type is used to identify what type of symbol this is.
	TokenType type;

	/**
	 * Token constructs a Token object.
	 * param t:    The type of token
	 * param loc:  The location of the token
	 * param val:  The value of the token (if applicable)
	 */
	Token(TokenType t = ERROR, const Location *loc = nullptr, std::string&& val = "");

	/**
	 * Token copy constructs a Token.
	 * param token: The Token to copy
	 */
	Token(const Token& token);

	/**
	 * Token move constructs a Token.
	 * param token: The Token to move
	 */
	Token(Token&& token);

	/**
	 * setValue sets the value field
	 * param val: the value to set the value field to
	 */
	void setValue(const std::string& val);

};

#endif

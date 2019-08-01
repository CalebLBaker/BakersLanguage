#ifndef SCANNER_H
#define SCANNER_H

#include <cctype>
#include "Token.h"
#include "Error.h"

// Scanner is a class that is used to tokenize a file.
class Scanner {

public:

	/**
 	 * Scanner constructs a Scanner object that will get symbols from a specified file.
	 * param infile_name: The name of the file that the Scanner will read symbols from
	 */
	Scanner(const char *infile_name);

	/**
	 * getNextToken reads the next token from the file.
	 * returns: the next token
	 */
	Token getNextToken();

	/** 
	 * matchNextToken consumes the next token and checks if it is of a given type.
	 * param type: the type to match the next token to
	 * returns:    true if the next token matched the specified type
	 */
	Error matchNextToken(TokenType type);

	/**
	 * isOpen indicates whether the Scanner has a file open.
	 * returns: true if a file is open
	 */
	bool isOpen() const;

	/**
	 * close closes the input file
	 * returns: true if the file was closed succcessfully
	 */
	bool close();

	// next_symbol is the next symbol that will be returned by getNextToken
	Token next_token;

private:

	FILE *file;
	Location location;

	const static std::string NON_ID_CHARS;

	void readNextToken();

	enum State {
		START,
		IN_IDENTIFIER
	};

};

#endif

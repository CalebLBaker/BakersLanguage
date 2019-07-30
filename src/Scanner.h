#include <cctype>
#include "Symbol.h"

// Scanner is a class that is used to tokenize a file.
class Scanner {

	/**
 	 * Scanner constructs a Scanner object that will get symbols from a specified file.
	 * param infile_name: The name of the file that the Scanner will read symbols from
	 */
	Scanner(const char *infile_name) : location(std::string(infile_name, 1, 0)) {
		file = fopen(infile_name, "r");
		readNextToken();
	}

	/**
	 * getNextToken reads the next token from the file.
	 * returns: the next token
	 */
	Symbol getNextToken() {
		Symbol ret = next_symbol;
		readNextToken();
		return ret;
	}

	/**
	 * isOpen indicates whether the Scanner has a file open.
	 * returns: true if a file is open
	 */
	bool isOpen() const {
		return file != nullptr;
	}

private:
	FILE *file;
	Symbol next_symbol;
	Location location;

	void readNextToken() {
		State state = START;
		std::string id = "";
		Location loc;
		while (true) {
			int next_char = fgetc(file);
			switch (state) {
				case START: {
					switch (next_char) {
						case '(': {
							location.column_number++;
							return Symbol(LEFT_PAREN, &location, "");
						}
						case ')': {
							location.column_number++;
							return Symbol(RIGHT_PAREN, &location, "");
						}
						case '{': {
							location.column_number++;
							return Symbol(LEFT_BRACE, &location, "");
						}
						case '}': {
							location.column_number++;
							return Symbol(RIGHT_BRACE, &location, "");
						}
						case '\n': {
							location.column_number = 0;
							location.line_number++;
							break;
						}
						case '\t': {
							location.column_number += (4 - location.column_number % 4);
							break;
						}
						case EOF: {
							return Symbol(END_OF_FILE, &location, "");
						}
						default : {
							location.column_number++;
							if (!isspace(next_char)) {
								state = IN_IDENTIFIER;
								loc = location;
								id += next_char;
							}
						}
					}
					break;
				}
				case IN_IDENTIFIER: {
					if (isspace(next_char) || NON_ID_CHARS.find(next_char) != std::string::npos) {
						ungetc(next_char, file);
						return Symbol(IDENTIFIER, &loc, id);
					}
					else {
						id += next_char;
						location.column_number++;
					}
				}
			}
		}
	}

	static const std::string NON_ID_CHARS = "(){}" + EOF;

	enum State {
		START,
		IN_IDENTIFIER
	};

};


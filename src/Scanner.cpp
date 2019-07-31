#include "Scanner.h"


const std::string Scanner::NON_ID_CHARS = "(){}";


Scanner::Scanner(const char *infile_name) : location(std::string(infile_name), 1, 0) {
	file = fopen(infile_name, "r");
	readNextToken();
}


Token Scanner::getNextToken() {
	Token ret = next_token;
	readNextToken();
	return ret;
}


Error Scanner::matchNextToken(TokenType type) {
	Error ret(SUCCESS, next_token.location);
	if (next_token.type == type) {
		ret.type = UNEXPECTED_TOKEN;
	}
	readNextToken();
	return ret;
}


bool Scanner::isOpen() const {
	return file != nullptr;
}


void Scanner::readNextToken() {
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
						next_token.type = LEFT_PAREN;
						next_token.location = location;
						return;
					}
					case ')': {
						location.column_number++;
						next_token.type = RIGHT_PAREN;
						next_token.location = location;
						return;
					}
					case '{': {
						location.column_number++;
						next_token.type = LEFT_BRACE;
						next_token.location = location;
						return;
					}
					case '}': {
						location.column_number++;
						next_token.type = RIGHT_BRACE;
						next_token.location = location;
						return;
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
						next_token.type = END_OF_FILE;
						next_token.location = location;
						return;
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
				bool new_token = NON_ID_CHARS.find(next_char) != std::string::npos;
				if (isspace(next_char) || new_token || next_char == EOF) {
					ungetc(next_char, file);
					next_token.type = IDENTIFIER;
					next_token.location = loc;
					next_token.setValue(id);
					return;
				}
				else {
					id += next_char;
					location.column_number++;
				}
			}
		}
	}
}


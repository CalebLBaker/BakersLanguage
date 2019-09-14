#include "Scanner.h"


const std::string Scanner::NON_ID_CHARS = "(){};=>[]";


Scanner::Scanner(const char *infile_name) : location(std::string(infile_name), 1, 0) {
	file = fopen(infile_name, "r");
	readNextToken();
}


Scanner::Scanner(Scanner&& old) : next_token(std::move(old.next_token)), file(old.file),
                                  location(std::move(old.location)) {}


Token Scanner::getNextToken() {
	Token ret = next_token;
	readNextToken();
	return ret;
}


Error Scanner::matchNextToken(Token::TokenType type) {
	Error ret(Error::SUCCESS, next_token.location);
	if (next_token.type != type) {
		std::string typeStr;
		switch (type) {
			case Token::IDENTIFIER: {
				typeStr = "an identifier.\n";
				break;
			}
			case Token::INTEGER: {
				typeStr = "an integer.\n";
				break;
			}
			case Token::STRING_LITERAL: {
				typeStr = "a string literal.\n";
			}
			default: {
				typeStr = "\"" + Token::tokenTypeToString(type) + "\".\n";
			}
		}
		ret.type = Error::UNEXPECTED_TOKEN;
		ret.message = "Unexpected token \"" + next_token.toString() + "\"; Expected " + typeStr;
	}
	readNextToken();
	return ret;
}


bool Scanner::isOpen() const {
	return file != nullptr;
}


bool Scanner::close() {
	return fclose(file) == 0;
}


void Scanner::readNextToken() {
	State state = START;
	std::string str = "";
	Location loc;
	while (true) {
		int next_char = fgetc(file);
		switch (state) {
			case START: {
				switch (next_char) {
					case '(': {
						location.column_number++;
						next_token.type = Token::LEFT_PAREN;
						next_token.location = location;
						return;
					}
					case ')': {
						location.column_number++;
						next_token.type = Token::RIGHT_PAREN;
						next_token.location = location;
						return;
					}
					case '{': {
						location.column_number++;
						next_token.type = Token::LEFT_BRACE;
						next_token.location = location;
						return;
					}
					case '}': {
						location.column_number++;
						next_token.type = Token::RIGHT_BRACE;
						next_token.location = location;
						return;
					}
					case '[': {
						location.column_number++;
						next_token.type = Token::LEFT_BRACKET;
						next_token.location = location;
						return;
					}
					case ']': {
						location.column_number++;
						next_token.type = Token::RIGHT_BRACKET;
						next_token.location = location;
						return;
					}
					case ';': {
						location.column_number++;
						next_token.type = Token::SEMICOLON;
						next_token.location = location;
						return;
					}
					case '=': {
						location.column_number++;
						state = HAVE_EQUAL;
						loc = location;
						break;
					}
					case '#': {
						location.column_number++;
						next_token.type = Token::CONST;
						next_token.location = location;
						return;
					}
					case '\"': {
						location.column_number++;
						state = IN_STRING;
						loc = location;
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
						next_token.type = Token::END_OF_FILE;
						next_token.location = location;
						return;
					}
					default : {
						location.column_number++;
						if (!isspace(next_char)) {
							state = IN_IDENTIFIER;
							loc = location;
							str += next_char;
						}
					}
				}
				break;
			}
			case HAVE_EQUAL: {
				if (next_token.type == '>') {
					next_token.type = Token::RETURN_SPECIFIER;
					location.column_number++;
				}
				else {
					next_token.type = Token::ASSIGNMENT_OPERATOR;
					ungetc(next_char, file);
				}
				next_token.location = loc;
				return;
			}
			case IN_STRING: {
				if (next_char == '\"') {
					next_token.type = Token::STRING_LITERAL;
					next_token.setStringValue(str);
					next_token.location = loc;
					return;
				}
				else {
					switch (next_char) {
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
							next_token.type = Token::ERROR;
							return;
						}
						case '\\': {
							location.column_number++;
							state = ESCAPE_SEQUENCE;
							break;
						}
						default: {
							location.column_number++;
						}
					}
					str += next_char;
					break;
				}
			}
			case ESCAPE_SEQUENCE: {
				switch (next_char) {
					case 'n': {
						location.column_number++;
						str += '\n';
						break;
					}
					case 't': {
						location.column_number++;
						str += '\t';
						break;
					}
					case '\n': {
						location.column_number = 0;
						location.line_number++;
						break;
					}
					case '\t': {
						location.column_number += (4 - location.column_number % 4);
						str += '\t';
						break;
					}
					case EOF: {
						next_token.type = Token::ERROR;
						return;
					}
					default: {
						location.column_number++;
						if (isdigit(next_char)) {
							str += next_char - '0';
						}
						else {
							str += next_char;
						}
					}
				}
			}
			case IN_IDENTIFIER: {
				bool new_token = NON_ID_CHARS.find(next_char) != std::string::npos;
				if (isspace(next_char) || new_token || next_char == EOF) {
					ungetc(next_char, file);
					next_token.location = loc;
					if (str == "return") {
						next_token.type = Token::RETURN;
					}
					else if (str == "class") {
						next_token.type = Token::CLASS;
					}
					else if (str == "func") {
						next_token.type = Token::FUNC;
					}
					else {
						next_token.type = Token::IDENTIFIER;
						next_token.setStringValue(str);
					}
					return;
				}
				else {
					str += next_char;
					location.column_number++;
				}
			}
		}
	}
}


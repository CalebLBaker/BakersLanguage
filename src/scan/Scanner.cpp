#include "Scanner.h"


const std::string Scanner::NON_ID_CHARS = "(){};=>[],.+-";


Scanner::Scanner(std::string_view infile_name) : location(infile_name, 1, 0) {
	file = fopen(infile_name.data(), "r");
	if (file != nullptr) {
		readNextToken();
	}
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
				break;
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
	if (file != nullptr) {
		bool ret = fclose(file) == 0;
		file = nullptr;
		return ret;
	}
	return true;
}


void Scanner::readNextToken() {
	State state = START;
	std::string str = "";
	int64_t int_val = 0;
	Location loc;
	while (true) {
		int next_char = fgetc(file);
		switch (state) {
			case START: {
				switch (next_char) {
					case '(': {
						location.column_number++;
						next_token.setType(Token::LEFT_PAREN);
						next_token.location = location;
						return;
					}
					case ')': {
						location.column_number++;
						next_token.setType(Token::RIGHT_PAREN);
						next_token.location = location;
						return;
					}
					case '{': {
						location.column_number++;
						next_token.setType(Token::LEFT_BRACE);
						next_token.location = location;
						return;
					}
					case '}': {
						location.column_number++;
						next_token.setType(Token::RIGHT_BRACE);
						next_token.location = location;
						return;
					}
					case '[': {
						location.column_number++;
						next_token.setType(Token::LEFT_BRACKET);
						next_token.location = location;
						return;
					}
					case ']': {
						location.column_number++;
						next_token.setType(Token::RIGHT_BRACKET);
						next_token.location = location;
						return;
					}
					case ';': {
						location.column_number++;
						next_token.setType(Token::SEMICOLON);
						next_token.location = location;
						return;
					}
					case ',': {
						location.column_number++;
						next_token.setType(Token::COMMA);
						next_token.location = location;
						return;
					}
					case '.': {
						location.column_number++;
						next_token.setType(Token::DOT);
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
						next_token.setType(Token::CONST);
						next_token.location = location;
						return;
					}
					case '\"': {
						location.column_number++;
						state = IN_STRING;
						loc = location;
						break;
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
						next_token.setType(Token::END_OF_FILE);
						next_token.location = location;
						return;
					}
					case '0': {
						location.column_number++;
						next_token.location = location;
						next_token.setType(Token::INTEGER);
						state = HAVE_ZERO;
						int_val = 0;
						break;
					}
					default : {
						location.column_number++;
						if (isdigit(next_char)) {
							next_token.location = location;
							next_token.setType(Token::INTEGER);
							state = DECIMAL_LITERAL;
							int_val = next_char - '0';
						}
						else if (!isspace(next_char)) {
							state = IN_IDENTIFIER;
							loc = location;
							str += (char)next_char;
						}
					}
				}
				break;
			}
			case HAVE_ZERO: {
				switch (next_char) {
					case 'b': {
						location.column_number++;
						state = BINARY_LITERAL;
						break;
					}
					case 'o': {
						location.column_number++;
						state = OCTAL_LITERAL;
						break;
					}
					case 'd': {
						location.column_number++;
						state = DECIMAL_LITERAL;
						break;
					}
					case 'x': {
						location.column_number++;
						state = HEXADECIMAL_LITERAL;
						break;
					}
					default: {
						if (isdigit(next_char)) {
							int_val = next_char - '0';
							location.column_number++;
							state = DECIMAL_LITERAL;
						}
						else {
							next_token.value.int_value = 0;
							ungetc(next_char, file);
							return;
						}
					}
				}
				break;
			}
			case BINARY_LITERAL: {
				if (next_char == '0' || next_char == '1') {
					location.column_number++;
					int_val = (int_val << 1) | (next_char ^ '0');
				}
				else {
					next_token.value.int_value = int_val;
					ungetc(next_char, file);
					return;
				}
				break;
			}
			case OCTAL_LITERAL: {
				if (next_char >= '0' && next_char < '8') {
					location.column_number++;
					int_val = (int_val << 3) | (next_char - '0');
				}
				else {
					next_token.value.int_value = int_val;
					ungetc(next_char, file);
					return;
				}
				break;
			}
			case DECIMAL_LITERAL: {
				if (isdigit(next_char)) {
					location.column_number++;
					int_val = (int_val * 10) + (next_char - '0');
				}
				else {
					next_token.value.int_value = int_val;
					ungetc(next_char, file);
					return;
				}
				break;
			}
			case HEXADECIMAL_LITERAL: {
				int64_t next_digit = 0;
				if (isdigit(next_char)) {
					next_digit = next_char - '0';
				}
				else if (next_char >= 'a' && next_char <= 'f') {
					next_digit = next_char - 87;
				}
				else if (next_char >= 'A' && next_char <= 'F') {
					next_digit = next_char - 55;
				}
				else {
					next_token.value.int_value = int_val;
					ungetc(next_char, file);
					return;
				}
				int_val = (int_val << 4) | next_digit;
				location.column_number++;
				break;
			}
			case HAVE_EQUAL: {
				if (next_char == '>') {
					next_token.setType(Token::RETURN_SPECIFIER);
					location.column_number++;
				}
				else {
					next_token.setType(Token::ASSIGNMENT_OPERATOR);
					ungetc(next_char, file);
				}
				next_token.location = loc;
				return;
			}
			case IN_STRING: {
				if (next_char == '\"') {
					next_token.setType(Token::STRING_LITERAL);
					next_token.setStringValue(str);
					next_token.location = loc;
					return;
				}
				else {
					switch (next_char) {
						case '\n': {
							location.column_number = 0;
							location.line_number++;
							str += (char)next_char;
							break;
						}
						case '\t': {
							location.column_number += (4 - location.column_number % 4);
							str += (char)next_char;
							break;
						}
						case EOF: {
							next_token.setType(Token::ERROR);
							return;
						}
						case '\\': {
							location.column_number++;
							state = ESCAPE_SEQUENCE;
							break;
						}
						default: {
							location.column_number++;
							str += (char)next_char;
						}
					}
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
						next_token.setType(Token::ERROR);
						return;
					}
					default: {
						location.column_number++;
						if (isdigit(next_char)) {
							str += (char)(next_char - '0');
						}
						else {
							str += (char)next_char;
						}
					}
				}
				state = IN_STRING;
				break;
			}
			case IN_IDENTIFIER: {
				bool new_token = NON_ID_CHARS.find((char)next_char) != std::string::npos;
				if (isspace(next_char) || new_token || next_char == EOF) {
					ungetc(next_char, file);
					next_token.location = loc;
					if (str == "return") {
						next_token.setType(Token::RETURN);
					}
					else if (str == "class") {
						next_token.setType(Token::CLASS);
					}
					else if (str == "func") {
						next_token.setType(Token::FUNC);
					}
					else if (str == "SYSCALL") {
						next_token.setType(Token::SYSCALL);
					}
					else if (str == "@entry") {
						next_token.setType(Token::ENTRY);
					}
					else {
						next_token.setType(Token::IDENTIFIER);
						next_token.setStringValue(str);
					}
					return;
				}
				else {
					str += (char)next_char;
					location.column_number++;
				}
			}
		}
	}
}


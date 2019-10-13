#include "gtest/gtest.h"

#include "scan/Token.h"

class TokenTest : public ::testing::Test {
	public:
		TokenTest() : l("llama.pdf", 42, 18), x(&l, 9), y(&l, "fox") {
		}

		~TokenTest() {
		}

		Location l;
		Token x;
		Token y;
};


TEST_F(TokenTest, defaultConstructorTest) {
	Token t(Token::RIGHT_PAREN, &l);
	EXPECT_EQ(t.type, Token::RIGHT_PAREN);
	EXPECT_EQ(t.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(t.value.int_value, 0);
}


TEST_F(TokenTest, identifierConstructorTest) {
	Token t(&l, "id");
	EXPECT_EQ(t.type, Token::IDENTIFIER);
	EXPECT_EQ(t.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(*t.value.str_value, std::string("id"));
}


TEST_F(TokenTest, intConstructorTest) {
	Token t(&l, 20);
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(t.value.int_value, 20);
}


TEST_F(TokenTest, copyConstructorTest) {
	Token t(x);
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(t.value.int_value, 9);
	Token u(y);
	EXPECT_EQ(u.type, Token::IDENTIFIER);
	EXPECT_EQ(u.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(*u.value.str_value, std::string("fox"));
}


TEST_F(TokenTest, moveConstructorTest) {
	Token t(std::move(x));
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(t.value.int_value, 9);
	EXPECT_EQ(x.type, Token::ERROR);
	EXPECT_EQ(x.value.str_value, nullptr);
}


TEST_F(TokenTest, assignmentOperatorTest) {
	Token t = std::move(x);
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), std::string("llama.pdf:42:18:"));
	EXPECT_EQ(t.value.int_value, 9);
	EXPECT_EQ(x.type, Token::ERROR);
	EXPECT_EQ(x.value.str_value, nullptr);
}


TEST_F(TokenTest, DestructorTest) {
	Token id(&l, "panda");
	Token num(&l, 14);
}


TEST_F(TokenTest, setStringValueTest) {
	y.setStringValue("land");
	EXPECT_EQ(*y.value.str_value, std::string("land"));
	EXPECT_EQ(y.type, Token::IDENTIFIER);
	x.value.str_value = 0;
	x.setStringValue("sea");
	EXPECT_EQ(*x.value.str_value, std::string("sea"));
	EXPECT_EQ(x.type, Token::IDENTIFIER);
}


TEST_F(TokenTest, setTypeTest) {
	x.setType(Token::IDENTIFIER);
	EXPECT_EQ(x.type, Token::IDENTIFIER);
	x.setType(Token::SEMICOLON);
	EXPECT_EQ(x.type, Token::SEMICOLON);
}


TEST_F(TokenTest, toStringTest) {
	EXPECT_EQ(x.toString(), "9");
	EXPECT_EQ(y.toString(), "fox");
	Token t(Token::SEMICOLON, &l);
	EXPECT_EQ(t.toString(), ";");
}


TEST_F(TokenTest, tokenTypeToStringTest) {
	EXPECT_EQ(Token::tokenTypeToString(Token::IDENTIFIER), "identifier");
	EXPECT_EQ(Token::tokenTypeToString(Token::LEFT_PAREN), "(");
	EXPECT_EQ(Token::tokenTypeToString(Token::RIGHT_PAREN), ")");
	EXPECT_EQ(Token::tokenTypeToString(Token::LEFT_BRACE), "{");
	EXPECT_EQ(Token::tokenTypeToString(Token::RIGHT_BRACE), "}");
	EXPECT_EQ(Token::tokenTypeToString(Token::LEFT_BRACKET), "[");
	EXPECT_EQ(Token::tokenTypeToString(Token::RIGHT_BRACKET), "]");
	EXPECT_EQ(Token::tokenTypeToString(Token::END_OF_FILE), "EOF");
	EXPECT_EQ(Token::tokenTypeToString(Token::RETURN), "return");
	EXPECT_EQ(Token::tokenTypeToString(Token::SEMICOLON), ";");
	EXPECT_EQ(Token::tokenTypeToString(Token::INTEGER), "integer");
	EXPECT_EQ(Token::tokenTypeToString(Token::CLASS), "class");
	EXPECT_EQ(Token::tokenTypeToString(Token::FUNC), "func");
	EXPECT_EQ(Token::tokenTypeToString(Token::RETURN_SPECIFIER), "=>");
	EXPECT_EQ(Token::tokenTypeToString(Token::CONST), "#");
	EXPECT_EQ(Token::tokenTypeToString(Token::ERROR), "Scanner Error");
	EXPECT_EQ(Token::tokenTypeToString(Token::STRING_LITERAL), "string");
	EXPECT_EQ(Token::tokenTypeToString(Token::ASSIGNMENT_OPERATOR), "=");
	EXPECT_EQ(Token::tokenTypeToString(Token::SYSCALL), "SYSCALL");
	EXPECT_EQ(Token::tokenTypeToString(Token::COMMA), ",");
	EXPECT_EQ(Token::tokenTypeToString(Token::DOT), ".");
	EXPECT_EQ(Token::tokenTypeToString(Token::ADD), "+");
	EXPECT_EQ(Token::tokenTypeToString(Token::SUBTRACT), "-");
}


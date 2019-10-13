#include "gtest/gtest.h"

#include "scan/Scanner.h"

class ScannerTest : public ::testing::Test {
	public:
		ScannerTest() {
			FILE *f = fopen("scannerTestFile.txt", "w");
			fprintf(f, "[](){};=#\"\n\t\\n\\t\\\n\\\t\\\"\\0a\"\nfunc\ta return=>class,0b101.0o512SYSCALL.0d193;0xf2A;0;015;32");
			fclose(f);
		}

		~ScannerTest() {
			remove("scannerTestFile.txt");
		}
};


TEST_F(ScannerTest, defaultConstructorTest) {
	Scanner s("scannerTestFile.txt");
	EXPECT_TRUE(s.isOpen());
	EXPECT_EQ(s.next_token.type, Token::LEFT_BRACKET);
	EXPECT_EQ(s.next_token.location.toString(), "scannerTestFile.txt:1:1:");
	Scanner t("doesntExist.dne");
	EXPECT_FALSE(t.isOpen());
}


TEST_F(ScannerTest, moveConstructorTest) {
	Scanner s("scannerTestFile.txt");
	Scanner t(std::move(s));
	EXPECT_TRUE(t.isOpen());
	EXPECT_EQ(t.next_token.type, Token::LEFT_BRACKET);
	EXPECT_EQ(t.next_token.location.toString(), "scannerTestFile.txt:1:1:");
	Token tok = t.getNextToken();
	EXPECT_EQ(tok.location.toString(), "scannerTestFile.txt:1:1:");
	Scanner u("doesntExist.dne");
	Scanner v(std::move(u));
	EXPECT_FALSE(v.isOpen());
}


TEST_F(ScannerTest, getNextTokenTest) {
	Scanner s("scannerTestFile.txt");
	Token t = s.getNextToken();
	EXPECT_EQ(t.type, Token::LEFT_BRACKET);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:1:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::RIGHT_BRACKET);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:2:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::LEFT_PAREN);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:3:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::RIGHT_PAREN);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:4:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::LEFT_BRACE);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:5:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::RIGHT_BRACE);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:6:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::SEMICOLON);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:7:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::ASSIGNMENT_OPERATOR);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:8:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::CONST);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:9:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::STRING_LITERAL);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:1:10:");
	std::string literal = "\n\t\n\t\t\"";
	literal += '\0';
	literal += 'a';
	EXPECT_EQ(*t.value.str_value, literal);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::FUNC);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:1:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::IDENTIFIER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:9:");
	EXPECT_EQ(*t.value.str_value, "a");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::RETURN);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:11:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::RETURN_SPECIFIER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:17:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::CLASS);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:19:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::COMMA);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:24:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:25:");
	EXPECT_EQ(t.value.int_value, 0b101);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::DOT);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:30:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:31:");
	EXPECT_EQ(t.value.int_value, 0b101001010);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::SYSCALL);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:36:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::DOT);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:43:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:44:");
	EXPECT_EQ(t.value.int_value, 193);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::SEMICOLON);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:49:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:50:");
	EXPECT_EQ(t.value.int_value, 0xF2A);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::SEMICOLON);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:55:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:56:");
	EXPECT_EQ(t.value.int_value, 0);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::SEMICOLON);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:57:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.value.int_value, 15);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:58:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::SEMICOLON);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:61:");
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::INTEGER);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:62:");
	EXPECT_EQ(t.value.int_value, 32);
	t = s.getNextToken();
	EXPECT_EQ(t.type, Token::END_OF_FILE);
	EXPECT_EQ(t.location.toString(), "scannerTestFile.txt:4:63:");
}


TEST_F(ScannerTest, matchNextTokenTest) {
	Scanner s("scannerTestFile.txt");
	EXPECT_TRUE(s.matchNextToken(Token::LEFT_BRACKET).ok());
	Error e = s.matchNextToken(Token::SEMICOLON);
	EXPECT_EQ(e.type, Error::UNEXPECTED_TOKEN);
	EXPECT_EQ(e.message, "Unexpected token \"]\"; Expected \";\".\n");
	e = s.matchNextToken(Token::IDENTIFIER);
	EXPECT_EQ(e.type, Error::UNEXPECTED_TOKEN);
	EXPECT_EQ(e.message, "Unexpected token \"(\"; Expected an identifier.\n");
	e = s.matchNextToken(Token::INTEGER);
	EXPECT_EQ(e.type, Error::UNEXPECTED_TOKEN);
	EXPECT_EQ(e.message, "Unexpected token \")\"; Expected an integer.\n");
	e = s.matchNextToken(Token::STRING_LITERAL);
	EXPECT_EQ(e.type, Error::UNEXPECTED_TOKEN);
	EXPECT_EQ(e.message, "Unexpected token \"{\"; Expected a string literal.\n");
}


TEST_F(ScannerTest, isOpenTest) {
	Scanner s("scannerTestFile.txt");
	EXPECT_TRUE(s.isOpen());
	Scanner t("dne.txt");
	EXPECT_FALSE(t.isOpen());
}



TEST_F(ScannerTest, closeTest) {
	Scanner s("scannerTestFile.txt");
	EXPECT_TRUE(s.close());
	EXPECT_FALSE(s.isOpen());
	Scanner t("dne.txt");
	EXPECT_TRUE(t.close());
	EXPECT_FALSE(t.isOpen());
}


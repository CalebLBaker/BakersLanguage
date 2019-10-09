#include "ast/SyntaxNode.h"

#include "gtest/gtest.h"

#include "ast/Scope.h"


class SyntaxNodeTest : public ::testing::Test {
	public:
		SyntaxNodeTest() {
		}

		~SyntaxNodeTest() {
		}

		Scope s;
};


class SyntaxNodeImp : public SyntaxNode {

public:

	SyntaxNodeImp(Scope *s = nullptr) : SyntaxNode(s) {}
	SyntaxNodeImp(SyntaxNodeImp &&old) : SyntaxNode(std::move(old)) {}

	Scope* getScope() {
		return scope;
	}
};


TEST_F(SyntaxNodeTest, defaultConstructorTest) {
	SyntaxNodeImp x(&s);
	EXPECT_EQ(x.getScope(), &s);
	EXPECT_EQ(x.location.toString(), std::string(":1:1:"));
}


TEST_F(SyntaxNodeTest, moveConstructorTest) {
	SyntaxNodeImp x(&s);
	x.location = Location("file.txt", 2, 4);
	SyntaxNodeImp y(std::move(x));
	EXPECT_EQ(y.getScope(), &s);
	EXPECT_EQ(y.location.toString(), std::string("file.txt:2:4:"));
}


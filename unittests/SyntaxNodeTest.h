#include "gtest/gtest.h"

#include "ast/SyntaxNode.h"
#include "ast/Namespace.h"


class SyntaxNodeTest : public ::testing::Test {
	public:
		SyntaxNodeTest() {
		}

		~SyntaxNodeTest() {
		}

		Namespace n;
		Scope s;
};


class SyntaxNodeImp : public SyntaxNode {

public:

	SyntaxNodeImp(Scope *s = nullptr, Namespace *n = nullptr) : SyntaxNode(s, n) {}
	SyntaxNodeImp(SyntaxNodeImp &&old) : SyntaxNode(std::move(old)) {}

	Namespace* getContext() {
		return context;
	}

	Scope* getScope() {
		return scope;
	}
};


TEST_F(SyntaxNodeTest, defaultConstructorTest) {
	SyntaxNodeImp x(&s, &n);
	EXPECT_EQ(x.getContext(), &n);
	EXPECT_EQ(x.getScope(), &s);
	EXPECT_EQ(x.location.toString(), std::string(":1:1:"));
}


TEST_F(SyntaxNodeTest, moveConstructorTest) {
	SyntaxNodeImp x(&s, &n);
	x.location = Location("file.txt", 2, 4);
	SyntaxNodeImp y(std::move(x));
	EXPECT_EQ(y.getContext(), &n);
	EXPECT_EQ(y.getScope(), &s);
	EXPECT_EQ(y.location.toString(), std::string("file.txt:2:4:"));
}


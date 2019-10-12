#ifndef DECLARATIONTEST_H
#define DECLARATIONTEST_H


#include "ast/Declaration.h"

#include "gtest/gtest.h"


class DeclarationImp : public Declaration {
	public:
		DeclarationImp(Scope *s) : Declaration(s) {}
		Error parse(Scanner *scanner) {
			return Error();
		}
		Scope* getScope() {
			return scope;
		}
};


TEST(DecarationTest, constructorTest) {
	Scope s;
	DeclarationImp x(&s);
	EXPECT_EQ(x.getScope(), &s);
	DeclarationImp y(nullptr);
	EXPECT_EQ(y.getScope(), nullptr);
}


#endif


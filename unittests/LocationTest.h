#include <cstdio>
#include "gtest/gtest.h"

#include "Location.h"


class LocationTest : public ::testing::Test {
	public:
		LocationTest() : x("testdata.txt", 2, 3) {
			FILE *f = fopen("testdata.txt", "w");
			fprintf(f, "line 1\nline 2\n");
			fclose(f);
		}

		~LocationTest() {
			remove("testdata.txt");
		}

		Location x;
};


TEST_F(LocationTest, defaultConstructorTest) {
	Location l("file", 4, 2);
	EXPECT_EQ(l.toString(), std::string("file:4:2:"));
}


TEST_F(LocationTest, copyConstructorTest) {
	Location l(x);
	EXPECT_EQ(l.toString(), std::string("testdata.txt:2:3:"));
}


TEST_F(LocationTest, pointerCopyConstructorTest) {
	Location l(nullptr);
	EXPECT_EQ(l.toString(), std::string(":1:1:"));
	Location m(&x);
	EXPECT_EQ(m.toString(), std::string("testdata.txt:2:3:"));
}


TEST_F(LocationTest, assignmentOperatorTest) {
	Location l = x;
	EXPECT_EQ(l.toString(), std::string("testdata.txt:2:3:"));
}


TEST_F(LocationTest, moveConstructorTest) {
	Location l(std::move(x));
	EXPECT_EQ(l.toString(), std::string("testdata.txt:2:3:"));
}


TEST_F(LocationTest, toStringTest) {
	EXPECT_EQ(x.toString(), std::string("testdata.txt:2:3:"));
}


TEST_F(LocationTest, getLineTest) {
	EXPECT_EQ(x.getLine(), std::string("line 2\n"));
	Location l("testdata.txt", 0);
	EXPECT_EQ(l.getLine(), std::string("\n"));
}


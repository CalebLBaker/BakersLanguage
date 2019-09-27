#include "gtest/gtest.h"

#include "Error.h"

class ErrorTest : public ::testing::Test {
	public:

		Location locA;
		Location locB;
		std::string msgA;
		std::string msgB;
		Error errA;
		Error errB;

		ErrorTest() : locA("file.cpp", 4, 2), locB("anotherFile", 83, 27), msgA("message"), msgB("longer message"), errA(Error::EXPECTED_IDENTIFIER, locA, msgA), errB(Error::NO_SUCH_TYPE, locB, msgB) {
		}

		~ErrorTest() {
		}
};


TEST_F(ErrorTest, defaultConstructorTest) {
	EXPECT_TRUE(Error().ok());
}


TEST_F(ErrorTest, memberMoveConstructorTest) {
	Error x(Error::EXPECTED_IDENTIFIER, std::move(locA), std::move(msgA));
	EXPECT_EQ(x.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(locA.toString(), ":4:2:");
	EXPECT_EQ(x.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(x.message, "message");
	EXPECT_EQ(msgA, "");

	Error y(Error::NO_SUCH_TYPE, std::move(locB), std::move(msgB));
	EXPECT_EQ(y.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(locB.toString(), ":83:27:");
	EXPECT_EQ(y.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(y.message, "longer message");
	EXPECT_EQ(msgB, "");
}


TEST_F(ErrorTest, memberCopyConstructorTest) {
	Error x(Error::EXPECTED_IDENTIFIER, locA, msgA);
	EXPECT_EQ(x.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(locA.toString(), "file.cpp:4:2:");
	EXPECT_EQ(x.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(x.message, "message");
	EXPECT_EQ(msgA, "message");

	Error y(Error::NO_SUCH_TYPE, locB, msgB);
	EXPECT_EQ(y.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(locB.toString(), "anotherFile:83:27:");
	EXPECT_EQ(y.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(y.message, "longer message");
	EXPECT_EQ(msgB, "longer message");
}


TEST_F(ErrorTest, moveConstructorTest) {
	Error x(std::move(errA));
	EXPECT_EQ(x.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(errA.location.toString(), ":4:2:");
	EXPECT_EQ(x.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(x.message, "message");
	EXPECT_EQ(errA.message, "");

	Error y(std::move(errB));
	EXPECT_EQ(y.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(errB.location.toString(), ":83:27:");
	EXPECT_EQ(y.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(y.message, "longer message");
	EXPECT_EQ(errB.message, "");
}


TEST_F(ErrorTest, copyConstructorTest) {
	Error x(errA);
	EXPECT_EQ(x.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(errA.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(x.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(errA.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(x.message, "message");
	EXPECT_EQ(errA.message, "message");

	Error y(errB);
	EXPECT_EQ(y.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(errB.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(y.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(errB.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(y.message, "longer message");
	EXPECT_EQ(errB.message, "longer message");
}


TEST_F(ErrorTest, moveAssignmentTest) {
	Error x;
	Error& ref = x = std::move(errA);
	EXPECT_EQ(&ref, &x);
	EXPECT_EQ(x.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(x.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(x.message, "message");
	EXPECT_EQ(errA.message, "");

	Error& refB = x = std::move(errB);
	EXPECT_EQ(&refB, &x);
	EXPECT_EQ(x.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(x.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(x.message, "longer message");
	EXPECT_EQ(errB.message, "");
}


TEST_F(ErrorTest, copyAssignmentTest) {
	Error x;
	Error& ref = x = errA;
	EXPECT_EQ(&ref, &x);
	EXPECT_EQ(x.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(errA.location.toString(), "file.cpp:4:2:");
	EXPECT_EQ(x.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(errA.type, Error::EXPECTED_IDENTIFIER);
	EXPECT_EQ(x.message, "message");
	EXPECT_EQ(errA.message, "message");

	Error& refB = x = errB;
	EXPECT_EQ(&refB, &x);
	EXPECT_EQ(x.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(errB.location.toString(), "anotherFile:83:27:");
	EXPECT_EQ(x.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(errB.type, Error::NO_SUCH_TYPE);
	EXPECT_EQ(x.message, "longer message");
	EXPECT_EQ(errB.message, "longer message");
}


TEST_F(ErrorTest, okTest) {
	Error x(Error::SUCCESS, locA, "");
	EXPECT_TRUE(x.ok());
	EXPECT_FALSE(errA.ok());
}


TEST_F(ErrorTest, toStringTest) {
	EXPECT_EQ(errA.toString(), "file.cpp:4:2: error: message");
	Error x(Error::EXPECTED_IDENTIFIER, locB, "");
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Expected an identifier.\n");
	x.type = Error::UNEXPECTED_TOKEN;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Unexpected token.\n");
	x.type = Error::DUPLICATE_FUNCTION_SIGNATURE;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Ambiguous function overload with same parameters.\n");
	x.type = Error::MAIN_NOT_FOUND;
	EXPECT_EQ(x.toString(), "error: No declaration found for function main.\n");
	x.type = Error::NO_SUCH_TYPE;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Undeclared type.\n");
	x.type = Error::DUPLICATE_TYPE;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Type has already been declared.\n");
	x.type = Error::DUPLICATE_VARIABLE;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Variable declared twice in the same scope.\n");
	x.type = Error::UNDECLARED_VARIABLE;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Variable not declared in this scope.\n");
	x.type = Error::TYPE_MISMATCH;
	EXPECT_EQ(x.toString(), "anotherFile:83:27: error: Incompatible types.\n");
	x.type = Error::SUCCESS;
	EXPECT_EQ(x.toString(), "anotherFile:83:27:\n");
}


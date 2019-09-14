#include "gtest/gtest.h"

#include "testfile.h"

class Test : public ::testing::Test {
	public:
		Test() {
		}

		~Test() {
		}
};


TEST_F(Test, test) {
}


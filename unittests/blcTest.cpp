#include "LocationTest.h"
#include "SyntaxNodeTest.h"
#include "TokenTest.h"
#include "ErrorTest.h"
#include "ScannerTest.h"
#include "DeclarationTest.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


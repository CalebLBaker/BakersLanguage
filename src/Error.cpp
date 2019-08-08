#include "Error.h"

Error::Error() : location(), type(SUCCESS) {}

Error::Error(ErrorType t, Location&& loc) : location(std::move(loc)), type(t) {}

Error::Error(ErrorType t, const Location& loc) : location(loc), type(t) {}

bool Error::ok() const {
	return type == SUCCESS;
}

std::string Error::toString() const {
	std::string ret = location.toString();
	switch (type) {
		case EXPECTED_IDENTIFIER: {
			return ret + " error: Expected an identifier.\n";
		}
		case UNEXPECTED_TOKEN: {
			return ret + " error: Unexpected token.\n";
		}
		case DUPLICATE_FUNCTION_SIGNATURE: {
			return ret + " error: Ambiguous function overload with same parameters.\n";
		}
		case MAIN_NOT_FOUND: {
			return "error: No declaration found for function main.\n";
		}
		default : {
			return ret;
		}
	}
}


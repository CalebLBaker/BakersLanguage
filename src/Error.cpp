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
		default : {
			return ret;
		}
	}
}


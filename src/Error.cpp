#include "Error.h"

Error err;

Error::Error() : location(), type(SUCCESS), message("") {}

Error::Error(ErrorType t, Location&& loc, std::string&& msg) : location(std::move(loc)), type(t), message(std::move(msg)) {}

Error::Error(ErrorType t, const Location& loc, const std::string& msg) : location(loc), type(t), message(msg) {}

Error::Error(const Error& original) : type(original.type), location(original.location), message(original.message) {}

Error::Error(Error&& old) : type(old.type), location(std::move(old.location)), message(std::move(old.message)) {

}

Error& Error::operator=(const Error& rhs) {
	type = rhs.type;
	location = rhs.location;
	message = rhs.message;
	return *this;
}

Error& Error::operator=(Error&& rhs) {
	type = rhs.type;
	location = std::move(rhs.location);
	message = std::move(rhs.message);
	return *this;
}

bool Error::ok() const {
	return type == SUCCESS;
}

std::string Error::toString() const {
	std::string ret = location.toString();
	if (!message.empty()) {
		return ret + " error: " + message;
	}
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
		case NO_SUCH_TYPE: {
			return ret + " error: Undeclared type.\n";
		}
		case DUPLICATE_TYPE: {
			return ret + " error: Type has already been declared.\n";
		}
		case DUPLICATE_VARIABLE: {
			return ret + " error: Variable declared twice in the same scope.\n";
		}
		case UNDECLARED_VARIABLE: {
			return ret + " error: Variable not declared in this scope.\n";
		}
		case TYPE_MISMATCH: {
			return ret + " error: Incompatible types.\n";
		}
		default : {
			return ret + '\n';
		}
	}
}


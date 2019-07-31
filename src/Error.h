#ifndef ERROR_H
#define ERROR_H

#include "Location.h"

// ErrorType is used for differentiating bettwen different types of errors.
enum ErrorType {
	SUCCESS,
	EXPECTED_IDENTIFIER,
	UNEXPECTED_TOKEN,
	NO_SUCH_TYPE
};

// Error is used for returning errors
class Error {
public:

	// Error constructs an error object indicating success
	Error() : location(), type(SUCCESS) {}

	// Error constructs an error message from an ErrorType and a Location
	Error(ErrorType t, Location&& loc) : location(std::move(loc)), type(t) {}

	// Error constructs an error message from an ErrorType and a location
	Error(ErrorType t, const Location& loc) : location(loc), type(t) {}

	// location is the location where the error happened
	Location location;

	// type indicates what type of error it is
	ErrorType type;

	/**
	 * ok indicates whether the operation in question was successful
	 * returns: true if the operation in question was successful
	 */
	bool ok() const {
		return type == SUCCESS;
	}

	/**
	 * toString converts the error message into a string.
	 * returns: the error message as a string
	 */
	std::string toString() const {
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
};

#endif

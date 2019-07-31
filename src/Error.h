#ifndef ERROR_H
#define ERROR_H

#include "Location.h"

// ErrorType is used for differentiating bettwen different types of errors.
enum ErrorType {
	SUCCESS,
	EXPECTED_IDENTIFIER,
	UNEXPECTED_TOKEN,
	NO_SUCH_TYPE,
	DUPLICATE_FUNCTION_SIGNATURE
};

// Error is used for returning errors
class Error {
public:

	// Error constructs an error object indicating success
	Error();

	// Error constructs an error message from an ErrorType and a Location
	Error(ErrorType t, Location&& loc);

	// Error constructs an error message from an ErrorType and a location
	Error(ErrorType t, const Location& loc);

	// location is the location where the error happened
	Location location;

	// type indicates what type of error it is
	ErrorType type;

	/**
	 * ok indicates whether the operation in question was successful
	 * returns: true if the operation in question was successful
	 */
	bool ok() const;

	/**
	 * toString converts the error message into a string.
	 * returns: the error message as a string
	 */
	std::string toString() const;

};

#endif

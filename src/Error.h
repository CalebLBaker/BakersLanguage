#ifndef ERROR_H
#define ERROR_H

#include "Location.h"

// Error is used for returning errors
class Error {
public:

	// ErrorType is used for differentiating bettwen different types of errors.
	enum ErrorType {
		SUCCESS,
		EXPECTED_IDENTIFIER,
		UNEXPECTED_TOKEN,
		NO_SUCH_TYPE,
		DUPLICATE_FUNCTION_SIGNATURE,
		MAIN_NOT_FOUND,
		DUPLICATE_TYPE,
		DUPLICATE_VARIABLE
	};

	// type indicates what type of error it is
	ErrorType type;

	// location is the location where the error happened
	Location location;

	// message is the error message that will be displayed to the user
	std::string message;

	// Error constructs an error object indicating success
	Error();

	// Error constructs an error message from an ErrorType and a Location
	Error(ErrorType t, Location&& loc, std::string&& msg = "");

	// Error constructs an error message from an ErrorType and a location
	Error(ErrorType t, const Location& loc, const std::string& msg = "");

	// Move constructor
	Error(Error&& old);

	// Copy constructor
	Error(const Error& original);

	// Assignment operator
	Error& operator=(const Error& rhs);

	// Move assignment
	Error& operator=(Error&& rhs);

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

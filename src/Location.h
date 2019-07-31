#ifndef LOCATION_H
#define LOCATION_H

#include <string>

// Location is a class used to represent a location in a file.
class Location {

public:

	// filename is the name of the file that the location is in.
	std::string filename;

	// line_number is the 1-indexed number of the line in the file.
	size_t line_number;

	// column_number is a 1-indexed number position in the line.
	size_t column_number;

	/**
	 * Location constructs a Location object
	 * param file: the name of the file
	 * param line: the line number
	 * param col:  the column number
	 */
	 Location(std::string file = "", size_t line = 1, size_t col = 1);

	/**
	 * Location copy constructs a Location from another Location
	 * param loc: The Location to copy
	 */
	Location(const Location& loc);

	/**
	 * Location copy constructs a location from a pointer
	 * param loc: The location pointer to copy from
	 */
	Location(const Location *loc);

	/**
	 * operator= copys one Location to another
	 * param rhs: the Location to copy
	 * returns: *this
	 */
	Location& operator=(const Location& rhs);

	/**
	 * Location move constructs a Location from another location
	 * param loc: The Location to move
	 */
	Location(Location&& loc);

	/**
	 * toString returns a string representation of the location.
	 * returns: a string representation of the location
	 */
	std::string toString() const;

};

#endif

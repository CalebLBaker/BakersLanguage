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
	 Location(std::string file = "", size_t line = 1, size_t col = 1) : filename(file),
	                                                                    line_number(line),
																		column_number(col) {}

	/**
	 * Location copy constructs a Location from another Location
	 * param loc: The Location to copy
	 */
	Location(const Location& loc) : filename(loc.filename), line_number(loc.line_number),
	                                column_number(loc.column_number) { }

	/**
	 * Location copy constructs a location from a pointer
	 * param loc: The location pointer to copy from
	 */
	Location(const Location *loc) {
		if (loc == nullptr) {
			filename = "";
			line_number = 1;
			column_number = 1;
		}
		else {
			*this = *loc;
		}
	}

	/**
	 * operator= copys one Location to another
	 * param rhs: the Location to copy
	 * returns: *this
	 */
	Location& operator=(const Location& rhs) {
		filename = rhs.filename;
		line_number = rhs.line_number;
		column_number = rhs.column_number;
		return *this;
	}

	/**
	 * Location move constructs a Location from another location
	 * param loc: The Location to move
	 */
	Location(Location&& loc) : filename(std::move(loc.filename)), line_number(loc.line_number),
	                           column_number(loc.column_number) {}

	/**
	 * toString returns a string representation of the location.
	 * returns: a string representation of the location
	 */
	std::string toString() const {
		std::string line_string = std::to_string(line_number);
		std::string column_string = std::to_string(column_number);
		return filename + ':' + line_string + ':' + column_string + ':';
	}

};

#endif

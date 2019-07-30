#include <string>

// Location is a class used to represent a location in a file.
class Location {

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
	 * Location constructs a Location from another Location
	 * param loc: The Location to copy
	 */
	Location(const Location *loc) {
		if (loc == nullptr) {
			filename = "";
			line = 1;
			col = 1;
		}
		else {
			filename = loc->filename;
			line_number = loc->line_number;
			column_number = loc->column_number;
		}
	}

	/**
	 * toString returns a string representation of the location.
	 * returns: a string representation of the location
	 */
	std::string toString() {
		std::string line_string = std::to_string(line_number);
		std::string column_string = std::to_string(column_number);
		return filename + ':' + line_string + ':' + column_string + ':';
	}

};

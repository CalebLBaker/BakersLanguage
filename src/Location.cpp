#include <fstream>

#include "Location.h"


Location::Location(const std::string& file, size_t line, size_t col) : filename(file), line_number(line),
													            column_number(col) {}

Location::Location(const Location& loc) : filename(loc.filename), line_number(loc.line_number),
								          column_number(loc.column_number) { }

Location::Location(const Location *loc) {
	if (loc == nullptr) {
		filename = "";
		line_number = 1;
		column_number = 1;
	}
	else {
		*this = *loc;
	}
}


Location& Location::operator=(const Location& rhs) {
	filename = rhs.filename;
	line_number = rhs.line_number;
	column_number = rhs.column_number;
	return *this;
}


Location::Location(Location&& loc) : filename(std::move(loc.filename)),
                                     line_number(loc.line_number), column_number(loc.column_number)
{}


std::string Location::toString() const {
	std::string line_string = std::to_string(line_number);
	std::string column_string = std::to_string(column_number);
	return filename + ':' + line_string + ':' + column_string + ':';
}


std::string Location::getLine() const {
	std::ifstream ifs(filename.c_str());
	std::string line;
	for (int i = 0; i < line_number; i++) {
		getline(ifs, line);
	}
	return line + '\n';
}


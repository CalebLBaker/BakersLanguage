#include "Location.h"

// SymbolType is an enumeration used to identify different types of symbols.
enum SymbolType {
	IDENTIFIER,
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACE,
	RIGHT_BRACE,
	END_OF_FILE,
	ERROR
};

// Symbol is a struct used to represent symbols from the input file.
struct Symbol {

	// location is the location of the symbol.
	Location location;

	// value is used to  store the value of an identifier.
	std::string *value;

	// type is used to identify what type of symbol this is.
	SymbolType type;

	/**
	 * Symbol constructs a Symbol object.
	 * param t:    The type of symbol
	 * param loc:  The location of the symbol
	 * param val:  The value of the symbol (if applicable)
	 */
	Symbol(SymbolType t, const Location *loc, std::string&& val = "") : type(t), location(loc),
	                                                                    value(val) {}
};

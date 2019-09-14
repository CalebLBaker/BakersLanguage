#ifndef TYPEMODIFIER_H
#define TYPEMODIFIER_H


#include <string>


namespace TypeModifier {

	// Type modifier modifies a type (making it into a pointer, array, slice, etc...)
	enum Modifier {
		SLICE,
		CONST
	};


	/**
	 * toString converts a type modifier into a string
	 * param mod: the type modifier to convert into a string
	 * returns:   the string representation of mod
	 */
	std::string toString(Modifier mod);

}


#endif


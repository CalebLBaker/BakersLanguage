#ifndef TYPEMODIFIER_H
#define TYPEMODIFIER_H


#include <string>


// Type modifier modifies a type (making it into a pointer, array, slice, etc...)
enum TypeModifier {
	SLICE
};


/**
 * toString converts a type modifier into a string
 * param mod: the type modifier to convert into a string
 * returns:   the string representation of mod
 */
std::string toString(TypeModifier mod);


#endif


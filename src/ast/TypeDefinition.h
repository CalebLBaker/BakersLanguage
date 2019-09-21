#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include <cstddef>
#include <string>

// TypeDefinition defines a data type
class TypeDefinition {
public:

	/**
	 * TypeDefinitions constructs a TypeDefinition
	 * param s: the size of the type
	 */
	TypeDefinition(size_t s = 0);

	// size is the size of the data type in bytes
	size_t size;

	/**
	 * stripConst returns the non-const definition of the type
	 */
	virtual const TypeDefinition* stripConst() const;

	/**
	 * toString returns the string representation of the type
	 * returns: the string representation of the type
	 */
	virtual std::string toString() const = 0;


};

#endif

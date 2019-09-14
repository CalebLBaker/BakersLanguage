#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include <cstddef>

// TypeDefinition defines a data type
class TypeDefinition {
public:

	/**
	 * TypeDefinitions constructs a TypeDefinition
	 * param k: the kind of type to define
	 */
	TypeDefinition(size_t s = 0, bool constant = false);

	// size is the size of the data type in bytes
	size_t size;

	// is_const indicates whether the type is a constant
	bool is_const;

};

#endif

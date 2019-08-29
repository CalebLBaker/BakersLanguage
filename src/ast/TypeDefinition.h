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
	TypeDefinition(size_t s = 0);

private:
	size_t size;
};

#endif

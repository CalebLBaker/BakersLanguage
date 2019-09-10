#ifndef ALIAS_H
#define ALIAS_H

#include "TypeDefinition.h"

// Alias defines an alias type that refers to another type
class Alias : TypeDefinition {

public:

	// Default constructor
	Alias(const TypeDefinition *ref = nullptr);

private:
	const TypeDefinition *referenced_type;

};

#endif


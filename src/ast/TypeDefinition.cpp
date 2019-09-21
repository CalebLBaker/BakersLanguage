#include "TypeDefinition.h"


TypeDefinition::TypeDefinition(size_t s) : size(s) {}


const TypeDefinition* TypeDefinition::stripConst() const {
	return this;
}


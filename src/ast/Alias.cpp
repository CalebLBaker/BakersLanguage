#include "Alias.h"


Alias::Alias(const std::string& alias_name, const TypeDefinition *ref) : name(alias_name), TypeDefinition(ref->size), referenced_type(ref) {}


std::string Alias::toString() const {
	return name;
}


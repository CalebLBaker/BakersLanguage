#include "Alias.h"


Alias::Alias(const std::string& alias_name, const TypeDefinition *ref) : name(alias_name), TypeDefinition(ref->size), referenced_type(ref) {}


std::string Alias::toString() const {
	return name;
}


Error Alias::assignRegisters(std::vector<int64_t> *registers) const {
	return referenced_type->assignRegisters(registers);
}


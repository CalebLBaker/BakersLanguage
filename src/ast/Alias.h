#ifndef ALIAS_H
#define ALIAS_H

#include "TypeDefinition.h"

// Alias defines an alias type that refers to another type
class Alias : public TypeDefinition {

public:

	// Default constructor
	Alias(const std::string& alias_name, const TypeDefinition *ref = nullptr);

	std::string toString() const;

	Error assignRegisters(std::vector<int64_t> *registers) const;

private:
	const TypeDefinition *referenced_type;
	std::string name;

};

#endif


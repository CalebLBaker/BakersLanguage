#ifndef POINTER_H
#define POINTER_H


#include "TypeDefinition.h"


class Pointer : public TypeDefinition {

public:

	// The type being pointed to
	const TypeDefinition *base_type;

	// Default constructor
	Pointer(const TypeDefinition *bt);

	std::string toString() const;

	Error assignRegisters(std::vector<int64_t> *registers) const;
	
};


#endif


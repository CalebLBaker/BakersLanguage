#ifndef CONSTANT_H
#define CONSTANT_H


#include "TypeDefinition.h"


class Constant : public TypeDefinition {

public:

	// Default Constructor
	Constant(const TypeDefinition *bt);

	// Move Constructor
	Constant(Constant&& old);

private:
	const TypeDefinition *base_type;

};


#endif

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "TypeDefinition.h"

class Primitive : public TypeDefinition {
public:
	Primitive(bool sign = true, size_t s = 0);
private:
	bool is_signed;
};

#endif


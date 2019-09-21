#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "TypeDefinition.h"

class Primitive : public TypeDefinition {
public:
	Primitive(std::string type_name, bool sign = true, size_t s = 0);
	std::string toString() const;
private:
	std::string name;
	bool is_signed;
};

#endif


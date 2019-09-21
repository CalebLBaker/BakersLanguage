#include "Primitive.h"


Primitive::Primitive(std::string type_name, bool sign, size_t s) : name(type_name), TypeDefinition(s), is_signed(sign) {}


std::string Primitive::toString() const {
	return name;
}


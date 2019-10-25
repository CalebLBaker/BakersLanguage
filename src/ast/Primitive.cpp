#include "Primitive.h"
#include "Program.h"


Primitive::Primitive(std::string type_name, bool sign, size_t s) : TypeDefinition(s), name(type_name), is_signed(sign) {}


std::string Primitive::toString() const {
	return name;
}


Error Primitive::assignRegisters(std::vector<int64_t> *registers) const {
	registers->push_back(Program::getNewRegister());
	return Error();
}


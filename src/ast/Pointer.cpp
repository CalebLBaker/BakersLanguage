#include "Pointer.h"
#include "Program.h"


Pointer::Pointer(const TypeDefinition *bt) : TypeDefinition(8), base_type(bt) {} 


std::string Pointer::toString() const {
	return "&" + base_type->toString();
}


Error Pointer::assignRegisters(std::vector<int64_t> *registers) const {
	registers->push_back(Program::getNewRegister());
	return Error();
}


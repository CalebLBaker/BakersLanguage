#include "Slice.h"
#include "Namespace.h"


Slice::Slice(const Pointer *ptr_type, Scope *s, Namespace *n) : ClassDeclaration(s, n), base_type(ptr_type->base_type) {
	addMember("ptr", ptr_type);
	addMember("size", UINT);
}


Slice::Slice(Slice&& old) : ClassDeclaration(std::move(old)), base_type(old.base_type) {}


std::string Slice::toString() const {
	return "[]" + base_type->toString();
}


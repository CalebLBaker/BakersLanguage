#include "Primitive.h"


const Type* Primitive::moveToHeap() {
	return new Primitive(std::move(*this));
}


size_t Primitive::hash() const {
	return TC_DATA;
}


bool Primitive::equal(const Type& rhs) const {
	return rhs.getCategory() == TC_DATA;
}


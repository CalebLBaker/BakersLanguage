#include "Primitive.h"


const Type* Primitive::moveToHeap() {
	return new Primitive(std::move(*this));
}


size_t Primitive::hash() const {
	return PRIMITIVE_MASK | mMask | (mSize << 3);
}


bool Primitive::equal(const Type& rhs) const {
	if (rhs.getCategory() != TC_DATA) {
		return false;
	}
	const Primitive *pRhs = (const Primitive*)&rhs;
	return pRhs->mMask == mMask && pRhs->mSize == mSize;
}


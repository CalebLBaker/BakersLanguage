#ifndef PRIMITIVE_H
#define PRIMITIVE_H


#include "Type.h"


class Primitive : public Type {
public:
	const static size_t UNSIGNED = 0;
	const static size_t SIGNED = 4;
	typedef size_t PrimitiveType;
	inline Primitive(PrimitiveType type, size_t size) : Type(TC_DATA), mMask(type), mSize(size) {}
	inline Primitive(Primitive&& old) : Type(std::move(old)), mMask(old.mMask), mSize(old.mSize) {}
protected:
	virtual const Type* moveToHeap();
	virtual size_t hash() const;
	virtual bool equal(const Type& rhs) const;
private:
	PrimitiveType mMask;
	size_t mSize;
};


#endif

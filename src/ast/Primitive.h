#ifndef PRIMITIVE_H
#define PRIMITIVE_H


#include "Type.h"


class Primitive : public Type {
public:
	inline Primitive() : Type(TC_DATA) {}
	inline Primitive(Primitive&& old) : Type(std::move(old)) {}
protected:
	virtual const Type* moveToHeap();
	virtual size_t hash() const;
	virtual bool equal(const Type& rhs) const;
};


#endif

#ifndef SLICE_H
#define SLICE_H


#include "ClassDeclaration.h"
#include "TypeDefinition.h"
#include "Pointer.h"


class Slice : public ClassDeclaration {

public:

	// Default constructor
	Slice(const Pointer *ptr_type, Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	Slice(Slice&& old);

	std::string toString() const;
	
private:
	const TypeDefinition *base_type;

};


#endif

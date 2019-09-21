#ifndef SLICE_H
#define SLICE_H


#include "ClassDeclaration.h"
#include "TypeDefinition.h"


class Slice : public ClassDeclaration {

public:

	// Default constructor
	Slice(const TypeDefinition *bt, Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	Slice(Slice&& old);

	std::string toString() const;
	
private:
	const TypeDefinition *base_type;

};


#endif

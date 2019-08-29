#ifndef CLASS_DECLARATION_H
#define CLASS_DECLARATION_H


#include "Error.h"
#include "scan/Scanner.h"
#include "TypeDefinition.h"
#include "SyntaxNode.h"


class ClassDeclaration : TypeDefinition, public SyntaxNode {

public:

	// Default constructor
	ClassDeclaration(Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	ClassDeclaration(ClassDeclaration&& old);

	// Name of the class
	std::string name;

	Error parse(Scanner *scanner);

};


#endif


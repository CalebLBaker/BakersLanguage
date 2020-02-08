#ifndef SYNTAX_NODE
#define SYNTAX_NODE

#include "Location.h"


class Scope;


// SyntaxNode is the base class inherited by abstract syntax tree nodes
class SyntaxNode {
	
public:

	// location is the location of the first symbol represented by this node
	Location location;

	// Default constructor
	SyntaxNode(Scope *s = nullptr);

	// Move constructor
	SyntaxNode(SyntaxNode&& old);

	Scope *scope;

};

#endif

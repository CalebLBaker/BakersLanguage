#ifndef SYNTAX_NODE
#define SYNTAX_NODE

#include "Location.h"

// SyntaxNode is the base class inherited by abstract syntax tree nodes
class SyntaxNode {
	
public:
	// location is the location of the first symbol represented by this node
	Location location;
};

#endif

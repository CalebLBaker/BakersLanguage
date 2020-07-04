#include "SyntaxNode.h"


SyntaxNode::SyntaxNode(Scope *s) : location(), scope(s) { } 


SyntaxNode::SyntaxNode(SyntaxNode&& old) : location(std::move(old.location)), scope(old.scope) {}


Error SyntaxNode::parse(Scanner*) {
	return Error();
}


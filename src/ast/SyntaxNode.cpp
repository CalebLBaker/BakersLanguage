#include "SyntaxNode.h"


SyntaxNode::SyntaxNode(Scope *s, Namespace *n) : location(), scope(s), context(n) {
	context = n;
	scope = s;
}


SyntaxNode::SyntaxNode(SyntaxNode&& old) : location(std::move(old.location)), scope(old.scope),
                                           context(old.context) {}


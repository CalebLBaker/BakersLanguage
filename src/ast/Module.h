#ifndef MODULE_H
#define MODULE_H


#include <memory>
#include <vector>

#include "Scope.h"
#include "SyntaxNode.h"
#include "Declaration.h"
#include "scan/Scanner.h"


class Module : SyntaxNode {
public:

	inline Module(Scope *pOwningScope) : SyntaxNode(pOwningScope), mScope(pOwningScope) {}

	Error parse(Scanner *pScanner);

	Error doSemanticAnalysis();

	Error genCode();

private:

	std::vector<std::unique_ptr<Declaration>> mDeclarations;
	Scope mScope;

};


#endif


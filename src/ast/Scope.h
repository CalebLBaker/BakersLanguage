#ifndef SCOPE_H
#define SCOPE_H


#include <unordered_map>

#include "Error.h"


class Declaration;


class Scope {
public:
	inline Scope(Scope *pOwningScope) : mpOwningScope(pOwningScope) {}
	Error addVariable(Declaration *pDecl);
	const Declaration* getVariable(std::string_view name);
private:
	std::unordered_map<std::string_view, Declaration*> mVariables;
	Scope *mpOwningScope;
};


#endif


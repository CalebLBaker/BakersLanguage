#ifndef SCOPE_H
#define SCOPE_H


#include <unordered_map>

#include "Declaration.h"


class Scope {
public:
	Error addVariable(Declaration *pDecl);
private:
	std::unordered_map<std::string_view, Declaration*> mVariables;
};


#endif


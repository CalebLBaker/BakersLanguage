#include "Scope.h"

#include "Declaration.h"


Error Scope::addVariable(Declaration *pDecl) {
	if (mVariables.emplace(pDecl->getName(), pDecl).second) {
		return Error();
	}
	else {
		return Error(Error::DUPLICATE_VARIABLE, pDecl->location);
	}
}


const Declaration* Scope::getVariable(std::string_view name) {
	for (Scope *pScope = this; pScope != nullptr; pScope = pScope->mpOwningScope) {
		auto pVariables = &pScope->mVariables;
		auto varIter = pVariables->find(name);
		if (varIter != pVariables->end()) {
			return varIter->second;
		}
	}
	return nullptr;
}

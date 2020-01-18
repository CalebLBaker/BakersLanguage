#include "Scope.h"


Error Scope::addVariable(Declaration *pDecl) {
	if (mVariables.emplace(pDecl->getName(), pDecl).second) {
		return Error();
	}
	else {
		return Error(Error::DUPLICATE_VARIABLE, pDecl->location);
	}
}


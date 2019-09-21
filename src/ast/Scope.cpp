#include "Scope.h"


Scope::Scope(Scope *s, Namespace *n) : owning_scope(s), owning_namespace(n) {}


const VariableDeclaration* Scope::getVarDecl(const std::string *name) const {
	for (const Scope *s = this; s != nullptr; s = s->owning_scope) {
		const std::unordered_map<std::string, VariableDeclaration*> *s_vars = &s->variables;
		auto v = s_vars->find(*name);
		if (v != s_vars->end()) {
			return v->second;
		}
	}
	return nullptr;
}


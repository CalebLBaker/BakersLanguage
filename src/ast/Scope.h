#ifndef SCOPE_H
#define SCOPE_H


#include <unordered_map>

#include "VariableDeclaration.h"


class Namespace;


class Scope {

public:

	// The containing namespace that the scope is in
	Namespace *owning_namespace;

	// Default constructor
	Scope(Scope *s = nullptr, Namespace *n = nullptr);

	/**
	 * getVarDecl gets the declaration of a variable that exists in this scope
	 * param name: the name of the variable to find the declaration for
	 * returns:    the declaration of the requested variable; nullptr if the variable does not
	 *             exist in this scope
	 */
	const VariableDeclaration* getVarDecl(const std::string *name) const;

private:
	std::unordered_map<std::string, VariableDeclaration*> variables;
	Scope *owning_scope;
};


#endif


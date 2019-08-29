#ifndef SCOPE_H
#define SCOPE_H


class Namespace;


class Scope {

public:

	// Default constructor
	Scope(Scope *s = nullptr, Namespace *n = nullptr);

	// The containing namespace that the scope is in
	Namespace *owning_namespace;

private:
	Scope *owning_scope;
};


#endif


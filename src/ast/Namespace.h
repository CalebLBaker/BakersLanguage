#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <memory>
#include <unordered_map>

#include "Scope.h"
#include "TypeDefinition.h"
#include "FunctionDeclaration.h"

// Namespace represents a scope in a program that can contain types, functions, and variables
class Namespace : public Scope {

public:

	// types maps type names to type definitions
	std::unordered_map<std::string, std::unique_ptr<TypeDefinition>> types;

	// functions maps function names to function declarations
	std::unordered_map<std::string, FunctionDeclaration*> functions;

	// Default constructor
	Namespace(Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	Namespace(Namespace&& old);

};

#endif


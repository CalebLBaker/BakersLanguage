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
	std::unordered_map<std::string, std::unique_ptr<const TypeDefinition>> types;

	// functions maps function names to function declarations
	std::unordered_map<std::string, FunctionDeclaration*> functions;

	// Default constructor
	Namespace(Scope *s = nullptr, Namespace *n = nullptr);

	// Move constructor
	Namespace(Namespace&& old);

	/**
	 * getDefinition gets the definition for a type if that type is declared in this namespace
	 * if the type has modifiers it will add a type definition for the modified type, provided
	 * the base type exists
	 * param type: the type to look for a defintion for
	 * returns:    a pointer to the defintion of type; nullptr if type doesn't exist in this
	 *             namespace
	 */
	const TypeDefinition* getDefinition(const Type *type);

private:

	const TypeDefinition* getDefinitionRecurse(const std::string *name, std::vector<TypeModifier::Modifier>::const_iterator modifier_begin, std::vector<TypeModifier::Modifier>::const_iterator modifier_end);

};

#endif


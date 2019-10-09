#ifndef SCOPE_H
#define SCOPE_H


#include <unordered_map>

#include "Alias.h"
#include "Primitive.h"
#include "VariableDeclaration.h"


class FunctionDeclaration;


class Scope {

public:

	// types maps type names to type definitions
	std::unordered_map<std::string, std::unique_ptr<TypeDefinition>> types;

	// functions maps function names to function declarations
	std::unordered_map<std::string, FunctionDeclaration*> functions;

	// Default constructor
	Scope(Scope *s = nullptr);

	// Move constructor
	Scope(Scope&& old);

	/**
	 * getDefinition gets the definition for a type if that type is declared in this namespace
	 * if the type has modifiers it will add a type definition for the modified type, provided
	 * the base type exists
	 * param type: the type to look for a defintion for
	 * returns:    a pointer to the defintion of type; nullptr if type doesn't exist in this
	 *             namespace
	 */
	const TypeDefinition* getDefinition(const Type *type);

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

	const TypeDefinition* getDefinitionRecurse(const std::string *name, std::vector<TypeModifier::Modifier>::const_iterator modifier_begin, std::vector<TypeModifier::Modifier>::const_iterator modifier_end);

};


extern Scope GLOBAL_SCOPE;
extern const Primitive *UINT64;
extern const Alias *UINT;


#endif


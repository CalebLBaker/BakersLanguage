#ifndef CLASS_DECLARATION_H
#define CLASS_DECLARATION_H


#include <unordered_map>

#include "Error.h"
#include "scan/Scanner.h"
#include "TypeDefinition.h"
#include "SyntaxNode.h"


class ClassDeclaration : public TypeDefinition, public SyntaxNode {

public:

	// Default constructor
	ClassDeclaration(Scope *s = nullptr);

	// Move constructor
	ClassDeclaration(ClassDeclaration&& old);

	// Name of the class
	std::string name;

	std::string toString() const;

	Error parse(Scanner *scanner);

	Error assignRegisters(std::vector<int64_t> *registers) const;

protected:

	void addMember(const std::string& name, const TypeDefinition *type);
	
private:
	std::unordered_map<std::string, const TypeDefinition*> member_map;
	std::vector<std::pair<std::string, const TypeDefinition*>> members;

};


#endif


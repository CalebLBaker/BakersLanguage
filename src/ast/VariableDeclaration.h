#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <memory>

#include "Statement.h"
#include "Type.h"
#include "Expression.h"

// VariableDeclaration represents the declaration of a variable
class VariableDeclaration : public Statement {

public:
	VariableDeclaration(Scope *s = nullptr, Namespace *n = nullptr);

	Error parse(Scanner *scanner);

	// Name of the variable
	std::string name;

	// The type of the variable
	std::unique_ptr<Type> type;

	Error doSemanticAnalysis();

private:
	std::unique_ptr<Expression> initializer;
};

#endif


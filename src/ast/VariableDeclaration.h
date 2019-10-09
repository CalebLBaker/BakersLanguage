#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <memory>

#include "Statement.h"
#include "Type.h"
#include "Expression.h"

// VariableDeclaration represents the declaration of a variable
class VariableDeclaration : public Statement {

public:
	VariableDeclaration(Scope *s = nullptr);

	Error parse(Scanner *scanner);

	// Name of the variable
	std::string name;

	// The type of the variable
	Type type;

	Error doSemanticAnalysis();

	/**
	 * assignRegisters assigns (a) virtual register(s) to the variable
	 * returns: An error object indicating whether any errors occurred
	 */
	Error assignRegisters();

	Error codeGen(std::vector<BasicBlock> *blocks) const;

private:
	std::unique_ptr<Expression> initializer;
	std::vector<int64_t> registers;
};

#endif


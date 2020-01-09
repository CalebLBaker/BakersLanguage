#include "VariableExpression.h"

#include "Scope.h"
#include "VariableDeclaration.h"


VariableExpression::VariableExpression(Scope *s) : Expression(s), var(nullptr) {}


const TypeDefinition* VariableExpression::getType() {
	if (var == nullptr) {
		return nullptr;
	}
	return var->type.definition;
}


Error VariableExpression::parse(Scanner*, Token&& look_ahead) {
	location = std::move(look_ahead.location);
	name = std::move(*look_ahead.value.str_value);
	return Error();
}


Error VariableExpression::doSemanticAnalysis() {
	var = scope->getVarDecl(&name);
	if (var == nullptr) {
		std::string message = "Variable \"" + name + "\" does not exist at this scope.";
		return Error(Error::UNDECLARED_VARIABLE, location, message);
	}
	return Error();
}


Error VariableExpression::codeGen(std::vector<BasicBlock> *blocks, const VariableDeclaration *target) const {
	if (target != nullptr) {
		auto lastBlock = &blocks->back();
		auto srcRegs = var->getRegisters();
		auto tgtRegs = target->getRegisters();
		auto end = tgtRegs->cend();
		for (auto src = srcRegs->cbegin(), tgt = tgtRegs->cbegin(); tgt != end; src++, tgt++) {
			lastBlock->addInstruction(Instruction(*tgt, *src));
		}
	}
	return Error();
}


#include "LiteralExpression.h"

#include "Program.h"


LiteralExpression::LiteralExpression(Scope *s) : Expression(s) {}


const TypeDefinition* LiteralExpression::getType() {
	return GLOBAL_SCOPE.types["#[]#byte"].get();
}


Error LiteralExpression::parse(Scanner*, Token&& look_ahead) {
	location = std::move(look_ahead.location);
	str_value = std::move(*look_ahead.value.str_value);
	return Error();
}


Error LiteralExpression::doSemanticAnalysis() {
	Program::addStringLiteral(str_value);
	return Error();
}


Error LiteralExpression::codeGen(std::vector<BasicBlock> *blocks, const VariableDeclaration *target) const {
	if (target != nullptr) {
		std::string label = Program::getLabel(str_value);
		auto last_block = &blocks->back();
		auto tgt = target->getRegisters()->cbegin();
		last_block->addInstruction(Instruction(*tgt, label));
		last_block->addInstruction(Instruction(tgt[1], std::to_string(str_value.size())));
	}
	return Error();
}


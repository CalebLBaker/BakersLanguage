#include "BasicBlock.h"


BasicBlock::BasicBlock() : instructions() {}


BasicBlock::BasicBlock(BasicBlock&& old) : instructions(std::move(old.instructions)) {}


void BasicBlock::addInstruction(Instruction&& inst) {
	instructions.emplace_back(inst);
}


Error BasicBlock::printCode(FILE *file) const {
	for (const Instruction& i : instructions) {
		TRY(i.printCode(file));
	}
	return Error();
}


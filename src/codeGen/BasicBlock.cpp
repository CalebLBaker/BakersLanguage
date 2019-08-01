#include "BasicBlock.h"

void BasicBlock::addInstruction(Instruction&& inst) {
	instructions.emplace_back(inst);
}


Error BasicBlock::printCode(FILE *file) const {
	for (const Instruction& i : instructions) {
		Error err = i.printCode(file);
		if (!err.ok()) {
			return err;
		}
	}
	return Error();
}


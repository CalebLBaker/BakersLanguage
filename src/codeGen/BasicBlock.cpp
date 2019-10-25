#include "BasicBlock.h"

#include "Function.h"


BasicBlock::BasicBlock() : instructions() {}


BasicBlock::BasicBlock(BasicBlock&& old) : instructions(std::move(old.instructions)) {}


void BasicBlock::addInstruction(Instruction&& inst) {
	instructions.emplace_back(std::move(inst));
}


Error BasicBlock::allocateRegisters(std::unordered_map<int64_t, int64_t> *reg_map, int64_t *next_real_reg) {
	for (Instruction& i : instructions) {
		switch(i.type) {
			case (Instruction::MOVE) : {
				allocateReg(reg_map, &i.source_a.reg_num, next_real_reg);
				break;
			}
			case (Instruction::MOVE_IMMEDIATE) : {
				allocateReg(reg_map, &i.destination, next_real_reg);
				break;
			}
			default : {
				continue;
			}
		}
	}
	if (*next_real_reg >= NUM_REAL_REGS) {
		return Error(Error::OUT_OF_REGISTERS, Location());
	}
	return Error();
}


Error BasicBlock::printCode(FILE *file) const {
	for (const Instruction& i : instructions) {
		TRY(i.printCode(file));
	}
	return Error();
}


void BasicBlock::allocateReg(std::unordered_map<int64_t, int64_t> *reg_map, int64_t *reg, int64_t *next_real_reg) {
	int64_t virtual_number = *reg;
	auto entry = reg_map->find(virtual_number);
	if (entry == reg_map->end()) {
		auto result = reg_map->emplace(virtual_number, *next_real_reg);
		(*next_real_reg)++;
		entry = result.first;
	}
	*reg = entry->second;
}


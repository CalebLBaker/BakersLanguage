#include "Function.h"
#include "globalDefines.h"


Function::Function() : blocks() {}


Function::Function(Function&& old) : blocks(std::move(old.blocks)) {}


Error Function::allocateRegisters() {
	std::unordered_map<int64_t, int64_t> reg_map;
	int64_t next_real_reg = 0;
	for (BasicBlock& i : blocks) {
		TRY(i.allocateRegisters(&reg_map, &next_real_reg));
	}
	return Error();
}


Error Function::printCode(FILE *file) const {
	for (const BasicBlock& i : blocks) {
		TRY(i.printCode(file));
	}
	return Error();
}


#include "Function.h"


Function::Function() : blocks() {}


Function::Function(Function&& old) : blocks(std::move(old.blocks)) {}


Error Function::printCode(FILE *file) const {
	for (const BasicBlock& i : blocks) {
		TRY(i.printCode(file));
	}
	return Error();
}


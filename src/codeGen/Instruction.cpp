#include "Instruction.h"


Instruction::Instruction(Mnemonic mnemonic) : type(mnemonic), name(nullptr) {}


Instruction::Instruction(const std::string *n) : type(LABEL), name(n) {}


Error Instruction::printCode(FILE *file) const {
	switch (type) {
		case RETURN: {
			fprintf(file, "\tret\n");
			break;
		}
		case LABEL: {
			fprintf(file, "%s:\n", name->c_str());
			break;
		}
	}
	return Error();
}


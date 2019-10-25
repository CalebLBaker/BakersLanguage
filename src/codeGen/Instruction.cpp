#include "globalDefines.h"
#include "Instruction.h"


#ifdef TARGET_WINDOWS
const char ENDL[3] = "\r\n";
#else
const char ENDL[2] = "\n";
#endif


#ifdef TARGET_X64
const int64_t NUM_REAL_REGS = 16;
const std::string REGISTERS[NUM_REAL_REGS] = {
	"r10", "r11", "r9", "r8", "rcx", "rdx", "rsi", "rdi", "rbx", "r12", "r13", "r14", "r15", "rbp"
};
#endif



Instruction::Instruction(Mnemonic mnemonic) : type(mnemonic) {}


Instruction::Instruction(const std::string *n) : type(LABEL) {
	source_a.immediate = n;
}


Instruction::Instruction(int64_t dest, int64_t src) : type(MOVE), destination(dest) {
	source_a.reg_num = src;
}


Instruction::Instruction(int64_t dest, const std::string& src) : type(MOVE_IMMEDIATE), destination(dest) {
	source_a.immediate = new std::string(src);
}


Instruction::Instruction(Instruction&& old) : type(old.type), destination(old.destination) {
	source_a.reg_num = old.source_a.reg_num;
	// Make sure old type is something that doesn't delete source_a.immediate
	old.type = RETURN;
}


Instruction::~Instruction() {
	if (type == MOVE_IMMEDIATE) {
		delete source_a.immediate;
	}
}


#ifdef TARGET_X64
Error Instruction::printCode(FILE *file) const {
	switch (type) {
		case RETURN: {
			fprintf(file, "\tret%s", ENDL);
			break;
		}
		case LABEL: {
			fprintf(file, "%s:%s", source_a.immediate->c_str(), ENDL);
			break;
		}
		case MOVE: {
			const char *dest_reg = REGISTERS[destination].c_str();
			const char *src_reg = REGISTERS[source_a.reg_num].c_str();
			fprintf(file, "\tmove %s, %s%s", dest_reg, src_reg, ENDL);
			break;
		}
		case MOVE_IMMEDIATE: {
			const char *dest_reg = REGISTERS[destination].c_str();
			fprintf(file, "\tmov %s, %s%s", dest_reg, source_a.immediate->c_str(), ENDL);
			break;
		}
	}
	return Error();
}
#endif


#include "globalDefines.h"
#include "Instruction.h"


#ifdef TARGET_WINDOWS
const char ENDL[2] = "\r\n";
#else
const char ENDL[1] = "\n";
#endif


Instruction::Instruction(Mnemonic mnemonic) : type(mnemonic), name(nullptr) {}


Instruction::Instruction(const std::string *n) : type(LABEL), name(n) {}


#ifdef TARGET_X64
Error Instruction::printCode(FILE *file) const {
	switch (type) {
		case RETURN: {
			fprintf(file, "\tret%s", ENDL);
			break;
		}
		case LABEL: {
			fprintf(file, "%s:%s", name->c_str(), ENDL);
			break;
		}
	}
	return Error();
}
#endif


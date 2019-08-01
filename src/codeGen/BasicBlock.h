#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include <vector>
#include "Instruction.h"

// BasicBlock represents a block of instructions such that are always executed in order
class BasicBlock {

public:
	/**
	 * addInstruction adds an instruction to the basic block
	 * param inst: the instruction to add
	 */
	void addInstruction(Instruction&& inst);

	/**
	 * printCode prints the assembly code to a file
	 * param file: the file to print to
	 * returns: an error object indicating any error that may have occurred
	 */
	Error printCode(FILE *file) const;

private:
	std::vector<Instruction> instructions;

};

#endif

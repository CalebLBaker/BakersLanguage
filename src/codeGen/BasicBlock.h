#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include <vector>
#include <unordered_map>

#include "Instruction.h"

// BasicBlock represents a block of instructions such that are always executed in order
class BasicBlock {

public:

	// Default constructor
	BasicBlock();

	// Move constructor
	BasicBlock(BasicBlock&& old);

	/**
	 * addInstruction adds an instruction to the basic block
	 * param inst: the instruction to add
	 */
	void addInstruction(Instruction&& inst);

	/**
	 * allocateRegisters replaces virtual register numbers with real register numbers
	 * param reg_map:       A map of virtual register number to real register numbers
	 * param next_real_reg: The next unused real register
	 * returns:             An error object indicating whether register allocation was successful
	 */
	Error allocateRegisters(std::unordered_map<int64_t, int64_t> *reg_map, int64_t *next_real_reg);

	/**
	 * printCode prints the assembly code to a file
	 * param file: the file to print to
	 * returns: an error object indicating any error that may have occurred
	 */
	Error printCode(FILE *file) const;

private:

	void allocateReg(std::unordered_map<int64_t, int64_t> *reg_map, int64_t *reg, int64_t *next_real_reg);

	std::vector<Instruction> instructions;

};

#endif

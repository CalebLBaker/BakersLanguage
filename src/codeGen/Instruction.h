#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include "Error.h"
#include "Value.h"

extern const size_t NUM_REAL_REGS;
//extern const std::string REGISTERS[NUM_REAL_REGS];

// Instruction represents a single intermediate low-level instruction
class Instruction {

public:

	// Mnemonic represents an instruction mnemonic
	enum Mnemonic {
		RETURN,
		LABEL,
		MOVE,
		MOVE_IMMEDIATE
	};

	// type is the mnemonic for the instruction
	Mnemonic type;

	// Register number of destination register
	int64_t destination;

	// Value of source parameter 1 or of label
	Value source_a;

	/**
	 * Instruction constructs an instruction
	 * param mnemonic: the mnemonic for the instruction
	 */
	Instruction(Mnemonic mnemonic);

	/**
	 * Instruction constructs a label instruction with a given name
	 * param n: the name to assign to the label
	 */
	Instruction(const std::string *n);

	/**
	 * Instruction constructs a move instruction
	 * param dest: the register to move to
	 * param src:  the register to move from
	 */
	Instruction(int64_t dest, int64_t src);

	/**
	 * Instruction constructs a move immediate instruction
	 * param dest: the register to move to
	 * param src:  the immediate value to move
	 */
	Instruction(int64_t dest, const std::string& src);

	// Move constructor
	Instruction(Instruction&& old);

	// ~Instruction destructs an Instruction
	~Instruction();

	/**
	 * printCode prints the assembly instruction to a file
	 * param file: the file to print to
	 * returns: an error object indicating any error that may have occurred
	 */
	Error printCode(FILE *file) const;

};

#endif

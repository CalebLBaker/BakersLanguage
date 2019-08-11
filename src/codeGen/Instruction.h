#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include "Error.h"

// Instruction represents a single intermediate low-level instruction
class Instruction {

public:

	// Mnemonic represents an instruction mnemonic
	enum Mnemonic {
		RETURN,
		LABEL
	};

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
	 * printCode prints the assembly instruction to a file
	 * param file: the file to print to
	 * returns: an error object indicating any error that may have occurred
	 */
	Error printCode(FILE *file) const;

private:

	// type is the mnemonic for the instruction
	Mnemonic type;

	// name is the name of the label for label instructions
	const std::string *name;

};

#endif

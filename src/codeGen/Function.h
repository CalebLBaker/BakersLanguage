#ifndef FUNCTION_H
#define FUNCTION_H

#include "BasicBlock.h"

// Function represents the intermediate low level code for a function
class Function {

public:

	// blocks is an array of all of the basic blocks in the function
	std::vector<BasicBlock> blocks;

	/**
	 * printCode prints the assembly code to a file
	 * param file: the file to print to
	 * returns: an error object indicating any error that may have occurred
	 */
	Error printCode(FILE *file) const;

};

#endif

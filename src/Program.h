#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include "FunctionDeclaration.h"
#include "TypeDefinition.h"

// Program is the root node of an abstract syntax tree
class Program : SyntaxNode {

public:
	// functions is a list of all functions in the global namespace
	std::vector<FunctionDeclaration> functions;

	/**
	 * parse parses the program
	 * param scanner: the scanner to parse tokens from
	 * returns:       an error object indicating any syntax error that may have occurred
	 */
	Error parse(Scanner *scanner) {
		location = scanner->next_token.location;
		while (scanner->next_token.type != END_OF_FILE) {
			functions.push_back(FunctionDeclaration());
			Error error = functions.back().parse(scanner);
			if (!error.ok()) {
				return error;
			}
		}
		return Error();
	}
};

#endif

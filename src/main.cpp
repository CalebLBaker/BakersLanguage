#include <cstdio>
#include "Scanner.h"

const int USAGE_ERROR = -1;
const int IO_ERROR = -2;

/**
 * main compiles Baker's Language source code into an executable.
 * param argc: The number of command line arguments
 * param argv: The command line arguments. An argument following a -o flag will be used as the
 *             output file. An argument that is not following a flag and is also not itself a flag
 *             will be used as the input file. If multiple input or output files are specified, the
 *             last one will be used.
 * returns:    0 on success; -1 on usage error; -2 on io error
 */
int main(int argc, char **argv) {

	// Process command line arguments
	const char *outfile_name = "out.bls";
	const char *infile_name = nullptr;
	bool o_flag = false;
	for (size_t i = 1; i < argc; i++) {
		if (o_flag) {
			outfile_name = argv[i];
			o_flag = false;
		}
		else if (argv[i][0] == '-') {
			for (char *j = argv[i] + 1; *j; j++) {
				if (*j == 'o') {
					o_flag = true;
					break;
				}
			}
		}
		else {
			infile_name = argv[i];
		}
	}

	// Ensure that infile can be read
	if (infile_name == nullptr) {
		fprintf(stderr, "error: no input file specified\n");
		return USAGE_ERROR;
	}

	Scanner scanner(infile_name);
	if (!scanner.isOpen()) {
		fprintf(stderr, "%s:0:0: error: cannot open file for reading\n", infile_name);
		return IO_ERROR;
	}

	// Read all the symbols
	// TODO: Do something with the symbols when they are read
	while (scanner.getNextToken().type != END_OF_FILE);

}
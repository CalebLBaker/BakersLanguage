#include <cstdio>
#include "parse/Program.h"

const int USAGE_ERROR = -1;
const int IO_ERROR = -2;
const int SYNTAX_ERROR = -3;
const int SEMANTIC_ERROR = -4;
const int CODE_GEN_ERROR = -5;

/**
 * main compiles Baker's Language source code into an executable.
 * param argc: The number of command line arguments
 * param argv: The command line arguments. An argument following a -o flag will be used as the
 *             output file. An argument that is not following a flag and is also not itself a flag
 *             will be used as the input file. If multiple input or output files are specified, the
 *             last one will be used.
 * returns:    0  : success
 *             -1 : usage error
 *             -2 : io error
 *             -3 : syntax error
 *             -4 : semantic error
 *             -5 : code generation error
 */
int main(int argc, char **argv) {

	// Process command line arguments
	const char *outfile_name = "out.s";
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

	// Scan and parse
	Program ast;
	Error err = ast.parse(&scanner);
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		return SYNTAX_ERROR;
	}

	// Close input file
	if (!scanner.close()) {
		fprintf(stderr, "%s:0:0: warning: error closing file\n", infile_name);
	}

	// Semantic analysis
	err = ast.doSemanticAnalysis();
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		return SEMANTIC_ERROR;
	}

	// Intermedate low level code generation
	err = ast.genCode();
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		return CODE_GEN_ERROR;
	}

	// Open output file
	FILE *outfile = fopen(outfile_name, "w");
	if (outfile == nullptr) {
		fprintf(stderr, "%s:0:0: error: cannot open file for writing\n", outfile_name);
		return IO_ERROR;
	}

	// Write code to file
	err = ast.printCode(outfile);
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		return CODE_GEN_ERROR;
	}

	// Close output file
	if (fclose(outfile) != 0) {
		fprintf(stderr, "%s:0:0: warning: error closing file\n", outfile_name);
		return IO_ERROR;
	}

	return 0;
}

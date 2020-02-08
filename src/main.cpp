#include <cstdio>
#include <filesystem>

#include "ast/Program.h"
#include "codeGen/CodeGen.h"

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
	std::string_view outfile = "";
	std::string_view infile = "";
	std::string_view filetypeString = "executable";
	std::string_view *pParamToWrite = &infile;
	bool generateAssembly = false;

	char **pArgEnd = argv + argc;
	for (char **pArgIter = argv + 1; pArgIter != pArgEnd; pArgIter++) {
		const char *pArg = *pArgIter;
		if (*pArg == '-') {
			switch (pArg[1]) {
				case '-': {
					std::string_view arg = pArg + 2;
					if (!arg.empty()) {
						size_t equalPos = arg.find('=');
						std::string_view argName = arg.substr(0, equalPos);
						if (argName == "outfile") {
							pParamToWrite = &outfile;
						}
						else if (argName == "infile") {
							pParamToWrite = &infile;
						}
						else if (argName == "filetype") {
							pParamToWrite = &filetypeString;
						}
						else {
							fprintf(stderr, "error: unrecognized argument \"%s\"\n", pArg);
							return -1;
						}
						if (equalPos != std::string_view::npos) {
							*pParamToWrite = arg.substr(equalPos + 1);
							pParamToWrite = &infile;
						}
					}
					break;
				}
				case 'o': {
					pParamToWrite = &outfile;
					break;
				}
				case 'i': {
					pParamToWrite = &infile;
					break;
				}
				case 'f': {
					pParamToWrite = &filetypeString;
					break;
				}
				case 'S': {
					generateAssembly = true;
					break;
				}
				default: {
					fprintf(stderr, "error: unrecognized flag \'%c\'\n", pArg[1]);
					return -1;
				}
			}
		}
		else {
			*pParamToWrite = pArg;
			pParamToWrite = &infile;
		}
	}

	// Ensure that infile can be read
	if (infile.empty()) {
		fprintf(stderr, "error: no input file specified\n");
		return USAGE_ERROR;
	}
	Scanner scanner(infile);
	if (!scanner.isOpen()) {
		fprintf(stderr, "%s:0:0: error: cannot open file for reading\n", infile.data());
		return IO_ERROR;
	}

	// Set the filetype variable
	CodeGen::FileType filetype;
	if (
		generateAssembly || filetypeString == "assembly" || filetypeString == "asm" ||
		filetypeString == "s"
	) {
		filetype = CodeGen::ASSEMBLY;
		filetypeString = "s";
	}
	else if (filetypeString == "executable" || filetypeString == "exe") {
		filetype = CodeGen::EXECUTABLE;
		filetypeString = "";
	}
	else {
		fprintf(stderr, "error: unrecognized file format requested: \"%s\"\n", filetypeString.data());
		return -1;
	}

	// Scan and parse
	Program ast;
	Error err = ast.parse(infile);
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		fprintf(stderr, err.location.getLine().c_str());
		return SYNTAX_ERROR;
	}

	// Close input file
	if (!scanner.close()) {
		fprintf(stderr, "%s:0:0: warning: error closing file\n", infile.data());
	}

	// Semantic analysis
	err = ast.doSemanticAnalysis();
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		fprintf(stderr, err.location.getLine().c_str());
		return SEMANTIC_ERROR;
	}

	// Intermedate low level code generation
	err = ast.genCode();
	if (!err.ok()) {
		fprintf(stderr, "%s", err.toString().c_str());
		fprintf(stderr, err.location.getLine().c_str());
		return CODE_GEN_ERROR;
	}

	// Set module name and such
	std::filesystem::path inpath = infile;
	inpath = inpath.filename();
	CodeGen::setModuleName(inpath.c_str());
	CodeGen::setSourceFilename(infile);

	// Generate an outfile name if none was provided
	if (outfile.empty()) {
		inpath.replace_extension(filetypeString);
		outfile = inpath.c_str();
	}

	// Print code
	CodeGen::generateOutput(filetype, outfile);

	return 0;

}

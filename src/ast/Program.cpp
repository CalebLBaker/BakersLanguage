#include "Program.h"


Error Program::parse(std::string_view filename) {
	Scanner scanner(filename);
	if (!scanner.isOpen()) {
		return Error(Error::IO_ERROR, Location(filename, 0, 0), "error: cannot open file for reading\n");
	}
	return mModules.emplace(std::string(filename), &mProgramScope).first->second.parse(&scanner);
}


Error Program::doSemanticAnalysis() {
	for (auto& [key, value] : mModules) {
		TRY(value.doSemanticAnalysis());
	}
	return Error();
}


Error Program::genCode() {
	for (auto& [key, value] : mModules) {
		TRY(value.genCode());
	}
	return Error();
}


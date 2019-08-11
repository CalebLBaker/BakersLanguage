#include "FunctionDeclaration.h"
#include "codeGen/Function.h"


Error FunctionDeclaration::parse(Scanner *scanner) {
	location = scanner->next_token.location;
	Error error = return_type.parse(scanner);
	if (!error.ok()) {
		return error;
	}
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.strValue));
	}
	else {
		return Error(EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	error = parameters.parse(scanner);
	if (!error.ok()) {
		return error;
	}
	return body.parse(scanner);
}


Error FunctionDeclaration::analyzeSignature(const Program *program) {
	return return_type.doSemanticAnalysis(program);
}


Error FunctionDeclaration::genCode(Function *low_level_func) {
	std::vector<BasicBlock> *blocks = &(low_level_func->blocks);
	blocks->emplace_back(BasicBlock());
	BasicBlock *block = &(blocks->back());
	block->addInstruction(Instruction(&name));
	block->addInstruction(Instruction(Instruction::RETURN));
	return Error();
}


#include "VariableDeclaration.h"
#include "Scope.h"
#include "Program.h"


VariableDeclaration::VariableDeclaration(Scope *s) : Statement(s), name(""), type(s) {}


VariableDeclaration::VariableDeclaration(Scope *s, Token&& look_ahead) : Statement(s), type(s, std::move(look_ahead)) {}



Error VariableDeclaration::parse(Scanner *scanner) {
	TRY(type.parse(scanner));
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER)
	{
		name = std::move(*next_token.value.str_value);
	}
	else
	{
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	next_token = scanner->getNextToken();
	switch (next_token.type) {
		case Token::SEMICOLON: {
			return Error();
		}
		case Token::ASSIGNMENT_OPERATOR: {
			initializer = std::make_unique<Expression>(scope);
			TRY(initializer->parse(scanner));
			return scanner->matchNextToken(Token::SEMICOLON);
		}
		default: {
			std::string message = "Unexpected token " + next_token.toString() + ". Expected \";\"";
			return Error(Error::UNEXPECTED_TOKEN, std::move(next_token.location), std::move(message));
		}
	}
}


Error VariableDeclaration::doSemanticAnalysis() {
	TRY(type.doSemanticAnalysis());
	if (initializer != nullptr) {
		TRY(initializer->doSemanticAnalysis());
	}
	const TypeDefinition *lvalue_type = type.definition;
	const TypeDefinition *rvalue_type = initializer->type;
	if (lvalue_type->stripConst() == rvalue_type->stripConst()) {
		return Error();
	}
	std::string message = "Cannot assign value of type " + rvalue_type->toString();
	message += " to a variable of type " + lvalue_type->toString();
	return Error(Error::TYPE_MISMATCH, location, message);
}


Error VariableDeclaration::assignRegisters() {
	return type.assignRegisters(&registers);
}


Error VariableDeclaration::codeGen(std::vector<BasicBlock> *blocks) const {
	BasicBlock *last_block = &blocks->back();
	if (initializer == nullptr) {
		return Error();
	}
	std::vector<int64_t>::const_iterator target = registers.cbegin();
	std::vector<int64_t>::const_iterator end = registers.cend();
	if (initializer->is_var) {
		const VariableDeclaration *source_var = scope->getVarDecl(&initializer->str_value);
		for (auto src = source_var->registers.cbegin(); target != end; target++, src++) {
			last_block->addInstruction(Instruction(*target, *src));
		}
	}
	else {
		// If we hit this block the variable is a slice of constant characters and the initializer
		// is a string literal
		std::string label = Program::getLabel(initializer->str_value);
		last_block->addInstruction(Instruction(*target, label));
		size_t size = initializer->str_value.size();
		last_block->addInstruction(Instruction(target[1], std::to_string(size)));
	}
	return Error();
}


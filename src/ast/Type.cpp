#include "Type.h"
#include "Program.h"

Error Type::parse(Scanner *scanner) {
	Token next_token = scanner->getNextToken();
	location = next_token.location;
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.strValue));
		return Error();
	}
	else {
		return Error(EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
}


Error Type::doSemanticAnalysis(const Program *program) {
	const std::unordered_map<std::string, TypeDefinition> *type_map = &(program->types);
	std::unordered_map<std::string, TypeDefinition>::const_iterator i = type_map->find(name);
	if (i == type_map->cend()) {
		return Error(NO_SUCH_TYPE, location);
	}
	else {
		definition = &(i->second);
		return Error();
	}
}

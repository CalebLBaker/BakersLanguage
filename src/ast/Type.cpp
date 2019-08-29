#include "Type.h"
#include "Program.h"


Type::Type(Scope *s, Namespace *n) : SyntaxNode(s, n), name(), definition(nullptr) {}


Type::Type(Type&& old) : SyntaxNode(std::move(old)), name(std::move(old.name)) {}


Error Type::parse(Scanner *scanner) {
	Token next_token = scanner->getNextToken();
	location = next_token.location;
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.strValue));
		return Error();
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
}


Error Type::doSemanticAnalysis() {
	for (Namespace *n = context; n != nullptr; n = n->owning_namespace) {
		auto type_map = &(n->types);
		auto i = type_map->find(name);
		if (i != type_map->cend()) {
			definition = i->second.get();
			return Error();
		}
	}
	std::string message = "Type \"" + name + "\" does not exist in this scope\n";
	return Error(Error::NO_SUCH_TYPE, location, message);
}

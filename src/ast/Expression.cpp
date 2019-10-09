#include "Expression.h"
#include "Scope.h"
#include "Program.h"


Expression::Expression(Scope *s) : SyntaxNode(s), type(nullptr) {}


Error Expression::parse(Scanner *scanner) {
	Token next_token = scanner->getNextToken();
	location = std::move(next_token.location);
	switch (next_token.type) {
		case Token::IDENTIFIER: {
			is_var = true;
			break;
		}
		case Token::STRING_LITERAL: {
			is_var = false;
			break;
		}
		default: {
			return Error(Error::UNEXPECTED_TOKEN, location);
		}
	}
	str_value = std::move(*next_token.value.str_value);
	return Error();
}


Error Expression::doSemanticAnalysis() {
	if (is_var) {
		const VariableDeclaration *var_decl = scope->getVarDecl(&str_value);
		if (var_decl == nullptr) {
			std::string message = "Variable \"" + str_value + "\" does not exist at this scope.";
			return Error(Error::UNDECLARED_VARIABLE, location, message);
		}
		type = var_decl->type.definition;
	}
	else {
		Program::addStringLiteral(str_value);
		type = GLOBAL_SCOPE.types["#[]#char"].get();
	}
	
	return Error();
}


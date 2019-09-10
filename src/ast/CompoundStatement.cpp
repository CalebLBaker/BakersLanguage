#include "CompoundStatement.h"
#include "VariableDeclaration.h"


CompoundStatement::CompoundStatement(Scope *s, Namespace *n) : Statement(s, n), statements() {
	int x = 2;
	int y = x + 3;
	}


CompoundStatement::CompoundStatement(CompoundStatement&& old) : Statement(std::move(old)), statements(std::move(old.statements)), local_scope(std::move(old.local_scope)), variables(std::move(old.variables))
{}


Error CompoundStatement::parse(Scanner *scanner) {
	Error result = scanner->matchNextToken(Token::LEFT_BRACE);
	location = result.location;
	if (!result.ok()) {
		return result;
	}

	Token *next_token = &scanner->next_token;
	Token::TokenType type;
	for (type = next_token->type; type != Token::RIGHT_BRACE; type = next_token->type) {
		Statement *new_statement = nullptr;
		switch (type) {
			case Token::LEFT_BRACE: {
				new_statement = (Statement*)new CompoundStatement(&local_scope, context);
				break;
			}
			case Token::LEFT_BRACKET:
			case Token::IDENTIFIER: {
				new_statement = (Statement*)new VariableDeclaration(&local_scope, context);
				break;
			}
			default: {
				std::string message = "Unexpected token \"" + next_token->toString() + "\"\n";
				return Error(Error::UNEXPECTED_TOKEN, next_token->location, message);
			}
		}
		statements.emplace_back(new_statement);
		result = new_statement->parse(scanner);
		if (!result.ok()) {
			return result;
		}
		if (type == Token::IDENTIFIER)
		{
			VariableDeclaration *var_decl = (VariableDeclaration*)new_statement;
			auto insert_result = variables.emplace(var_decl->name, var_decl);
			if (!insert_result.second)
			{
				return Error(Error::DUPLICATE_VARIABLE, new_statement->location);
			}
		}
	}

	result = scanner->matchNextToken(Token::RIGHT_BRACE);
	return result;
}


Error CompoundStatement::doSemanticAnalysis() {
	std::vector<std::unique_ptr<Statement>>::iterator end = statements.end();
	for (std::vector<std::unique_ptr<Statement>>::iterator i = statements.begin(); i != end; i++) {
		Error result = (*i)->doSemanticAnalysis();
		if (!result.ok()) {
			return result;
		}
	}
	return Error();
}


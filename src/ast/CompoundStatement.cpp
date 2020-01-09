#include "CompoundStatement.h"
#include "ExpressionStatement.h"
#include "VariableDeclaration.h"


CompoundStatement::CompoundStatement(Scope *s) : Statement(s), statements(), local_scope(s) { } 

CompoundStatement::CompoundStatement(CompoundStatement&& old) : Statement(std::move(old)), statements(std::move(old.statements)), variables(std::move(old.variables)), local_scope(std::move(old.local_scope))
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
		bool is_var_decl = false;
		switch (type) {
			case Token::LEFT_BRACE: {
				new_statement = (Statement*)new CompoundStatement(&local_scope);
				break;
			}
			case Token::INTEGER:
			case Token::STRING_LITERAL:
			case Token::SYSCALL: {
				new_statement = new ExpressionStatement(&local_scope);
				break;
			}
			case Token::LEFT_BRACKET: {
				is_var_decl = true;
				new_statement = (Statement*)new VariableDeclaration(&local_scope);
				break;
			}
			case Token::IDENTIFIER: {
				Token t = scanner->getNextToken();
				if (next_token->type == Token::IDENTIFIER) {
					is_var_decl = true;
					new_statement = new VariableDeclaration(&local_scope, std::move(t));
				}
				else {
					new_statement = new ExpressionStatement(&local_scope, std::move(t));
				}
				break;
			}
			default: {
				std::string message = "Unexpected token \"" + next_token->toString() + "\"\n";
				return Error(Error::UNEXPECTED_TOKEN, next_token->location, message);
			}
		}
		statements.emplace_back(new_statement);
		TRY(new_statement->parse(scanner));
		if (is_var_decl)
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
		TRY((*i)->doSemanticAnalysis());
	}
	return Error();
}


Error CompoundStatement::codeGen(std::vector<BasicBlock> *blocks) const {
	for (const auto& [key, value] : variables) {
		TRY(value->assignRegisters());
	}
	for (const std::unique_ptr<Statement>& i : statements) {
		TRY(i->codeGen(blocks));
	}
	return Error();
}


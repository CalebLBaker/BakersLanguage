#include "globalDefines.h"
#include "Program.h"
#include "Primitive.h"
#include "ClassDeclaration.h"


Program::Program() : main(nullptr), global_namespace() {
	global_namespace.types.emplace("void", (TypeDefinition*)new Primitive(false, 0));
	global_namespace.types.emplace("uint8", (TypeDefinition*)new Primitive(false, 1));
	global_namespace.types.emplace("uint16", (TypeDefinition*)new Primitive(false, 2));
	global_namespace.types.emplace("uint32", (TypeDefinition*)new Primitive(false, 4));
	global_namespace.types.emplace("uint64", (TypeDefinition*)new Primitive(false, 8));
	global_namespace.types.emplace("sint8", (TypeDefinition*)new Primitive(true, 1));
	global_namespace.types.emplace("sint16", (TypeDefinition*)new Primitive(true, 2));
	global_namespace.types.emplace("sint32", (TypeDefinition*)new Primitive(true, 4));
	global_namespace.types.emplace("sint64", (TypeDefinition*)new Primitive(true, 8));
}


Program::Program(Program&& old) : SyntaxNode(std::move(old)), function_list(std::move(old.function_list)), code(std::move(old.code)), main(old.main), global_namespace(std::move(old.global_namespace)) {}


Error Program::parse(Scanner *scanner) {
	location = scanner->next_token.location;
	Token *next_token = &scanner->next_token;
	Token::TokenType type;
	for (type = next_token->type; type != Token::END_OF_FILE; type = next_token->type) {
		switch (type) {
			case Token::CLASS: {
				ClassDeclaration *class_decl = new ClassDeclaration(&global_namespace, &global_namespace);
				class_decl->parse(scanner);
				std::string *name = &class_decl->name;
				auto result = global_namespace.types.emplace(*name, (TypeDefinition*)class_decl);
				if (!result.second) {
					return Error(Error::DUPLICATE_TYPE, class_decl->location);
				}
				break;
			}
			case Token::IDENTIFIER: {
				function_list.push_back(FunctionDeclaration(&global_namespace, &global_namespace));
				Error error = function_list.back().parse(scanner);
				if (!error.ok()) {
					return error;
				}
				break;
			}
			default: {
				std::string message = "Unexpected token \"" + next_token->toString();
				message.append("\" found in global scope.");
				return Error(Error::UNEXPECTED_TOKEN, next_token->location, message);
			}
		}
	}
	return Error();
}


Error Program::doSemanticAnalysis() {
	for (FunctionDeclaration& i : function_list) {
		Error err = i.analyzeSignature();
		if (!err.ok()) {
			return err;
		}
		if (!global_namespace.functions.emplace(i.name, &i).second) {
			return Error(Error::DUPLICATE_FUNCTION_SIGNATURE, i.location);
		}
		if (i.name == "main")
		{
			main = &i;
		}
	}
	for (FunctionDeclaration& i : function_list) {
		Error err = i.doSemanticAnalysis();
		if (!err.ok()) {
			return err;
		}
	}
	return main != nullptr ? Error() : Error(Error::MAIN_NOT_FOUND, Location());
}


Error Program::genCode() {
	for (FunctionDeclaration& i : function_list) {
		code.emplace_back(Function());
		Error err = i.genCode(&(code.back()));
		if (!err.ok()) {
			return err;
		}
	}
	return Error();
}


Error Program::printCode(FILE *file) const {
#ifdef TARGET_X64
 #ifdef TARGET_UNIX
 	fprintf(file, "GLOBAL _start\n_start:\n");
	
	/*
	if main has parameters:
		fprintf(file, "\tmov rdi, [rsp]\n\tlea rsi, [rsp+8]\n");
	*/

	fprintf(file, "\tcall main\n");

	/*
	if main returns a value:
		fprintf(file, "\tmov rdi, rax\n");
	else:
	*/
	fprintf(file, "\txor rdi, rdi\n");

	fprintf(file, "\tmov rax, 0x3C\n\tsyscall\n");
 #endif
#endif
	for (const Function& i : code) {
		Error err = i.printCode(file);
		if (!err.ok()) {
			return err;
		}
	}
	return Error();
}


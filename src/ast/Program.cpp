#include "globalDefines.h"
#include "Program.h"
#include "Primitive.h"
#include "Alias.h"
#include "ClassDeclaration.h"


std::unordered_set<std::string> string_literals;


Program::Program() : main(nullptr) {
	GLOBAL_SCOPE.types.emplace("uint8", (TypeDefinition*)new Primitive("uint8", false, 1));
	GLOBAL_SCOPE.types.emplace("uint16", (TypeDefinition*)new Primitive("uint16", false, 2));
	GLOBAL_SCOPE.types.emplace("uint32", (TypeDefinition*)new Primitive("uint32", false, 4));
	GLOBAL_SCOPE.types.emplace("uint64", (TypeDefinition*)new Primitive("uint64", false, 8));
	GLOBAL_SCOPE.types.emplace("sint8", (TypeDefinition*)new Primitive("sint8", true, 1));
	GLOBAL_SCOPE.types.emplace("sint16", (TypeDefinition*)new Primitive("sint16", true, 2));
	GLOBAL_SCOPE.types.emplace("sint32", (TypeDefinition*)new Primitive("sint32", true, 4));
	GLOBAL_SCOPE.types.emplace("sint64", (TypeDefinition*)new Primitive("sint64", true, 8));
	TypeDefinition *char8  = new Primitive("char8", false, 1);
	TypeDefinition *char_type = new Alias("char", char8);
	TypeDefinition *const_char = new Constant(char_type);
	TypeDefinition *slice_const_char = new Slice(const_char);
	TypeDefinition *const_slice_const_char = new Constant(slice_const_char);
	GLOBAL_SCOPE.types.emplace("char8", char8);
	GLOBAL_SCOPE.types.emplace("char", char_type);
	GLOBAL_SCOPE.types.emplace("#char", const_char);
	GLOBAL_SCOPE.types.emplace("[]#char", slice_const_char);
	GLOBAL_SCOPE.types.emplace("#[]#char", const_slice_const_char);
}


Program::Program(Program&& old) : SyntaxNode(std::move(old)), function_list(std::move(old.function_list)), code(std::move(old.code)), main(old.main) {}


Error Program::parse(Scanner *scanner) {
	location = scanner->next_token.location;
	Token *next_token = &scanner->next_token;
	Token::TokenType type;
	for (type = next_token->type; type != Token::END_OF_FILE; type = next_token->type) {
		switch (type) {
			case Token::CLASS: {
				ClassDeclaration *class_decl = new ClassDeclaration(&GLOBAL_SCOPE, &GLOBAL_SCOPE);
				class_decl->parse(scanner);
				std::string *name = &class_decl->name;
				auto result = GLOBAL_SCOPE.types.emplace(*name, (TypeDefinition*)class_decl);
				if (!result.second) {
					return Error(Error::DUPLICATE_TYPE, class_decl->location);
				}
				break;
			}
			case Token::FUNC: {
				function_list.push_back(FunctionDeclaration(&GLOBAL_SCOPE, &GLOBAL_SCOPE));
				TRY(function_list.back().parse(scanner));
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
		TRY(i.analyzeSignature());
		if (!GLOBAL_SCOPE.functions.emplace(i.name, &i).second) {
			return Error(Error::DUPLICATE_FUNCTION_SIGNATURE, i.location);
		}
		if (i.name == "main")
		{
			main = &i;
		}
	}
	for (FunctionDeclaration& i : function_list) {
		TRY(i.doSemanticAnalysis());
	}
	return main != nullptr ? Error() : Error(Error::MAIN_NOT_FOUND, Location());
}


Error Program::genCode() {
	for (FunctionDeclaration& i : function_list) {
		code.emplace_back(Function());
		TRY(i.genCode(&(code.back())));
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
		TRY(i.printCode(file));
	}
	return Error();
}


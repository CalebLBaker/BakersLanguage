#include "Module.h"


Error Module::parse(Scanner *pScanner) {
	location = pScanner->next_token.location;
	Token *pNextToken = &pScanner->next_token;
	for (auto type = pNextToken->type; type != Token::END_OF_FILE; type = pScanner->next_token.type) {
		switch (type) {
			case Token::ENTRY: {
				Declaration *decl = new Declaration(&mScope);
				mDeclarations.emplace_back(decl);
				entryPoints.emplace_back(decl);
				TRY(decl->parse(pScanner));
				break;
			}
			case Token::FUNC: {
				Declaration *pDecl = new Declaration(&mScope);
				mDeclarations.emplace_back(pDecl);
				TRY(pDecl->parse(pScanner));
				break;
			}
			default: {
				std::string message = "Unexpected token \"" + pNextToken->toString();
				message.append("\" found in global scope.\n");
				return Error(Error::UNEXPECTED_TOKEN, pNextToken->location, message);
			}
		}
	}
	return Error();
}


Error Module::doSemanticAnalysis() {
	for (std::unique_ptr<Declaration>& pDecl : mDeclarations) {
		TRY(pDecl->doSemanticAnalysis());
	}
	return Error();
}


Error Module::genCode() {
	for (std::unique_ptr<Declaration>& pDecl : mDeclarations) {
		TRY(pDecl->genCode());
	}
	return Error();
}


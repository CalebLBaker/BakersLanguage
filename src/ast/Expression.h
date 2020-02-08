#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <memory>

#include "SyntaxNode.h"
#include "Type.h"
#include "scan/Scanner.h"


class Expression : public SyntaxNode {
public:
	static Error NewExpression(Scanner *pScanner, Scope *pScope, std::unique_ptr<Expression> *pOut);
	Expression(Scope *pScope);
	virtual Error parse(Scanner *pScanner) = 0;
	virtual Error doSemanticAnalysis() = 0;
	virtual const Type* getTypeValue() = 0;
	const Type* getType() const;
	static bool inFirstSet(Token::TokenType type) {
		return type == Token::FUNC || type == Token::IDENTIFIER;
	}
protected:
	const Type *mpType;
};


#endif


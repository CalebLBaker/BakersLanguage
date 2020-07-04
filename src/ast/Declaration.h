#ifndef DECLARATION_H
#define DECLARATION_H


#include <memory>

#include "Error.h"
#include "Expression.h"
#include "Scope.h"
#include "Statement.h"
#include "scan/Scanner.h"


class Declaration : public Statement {
public:

	Declaration(Scope *pScope);

	Declaration(std::string_view name, Scope *pScope) :
		Statement(pScope), mName(name), mpType(Type::TYPE), entryPoint(false)
	{
		pScope->addVariable(this);
	}

	inline Declaration(std::unique_ptr<Expression>&& pType) :
		Statement(pType->scope),
		mpType(nullptr),
		mpValue(nullptr),
		mpTypeExpression(std::move(pType)),
		mInitiailizerType(NONE),
		entryPoint(false)
	{}

	inline Declaration(std::string_view name, const Type *pValue, Scope *pScope) :
		Declaration(name, pScope)
	{
		mpValue = pValue;
	}

	constexpr void setTypeValue(const Type *pValue) {
		mpValue = pValue;
	}

	Error parse(Scanner *pScanner);

	Error doSemanticAnalysis();

	std::string_view getName() const;

	inline const Type* getType() const {
		return mpType;
	}

	inline const Type* getTypeValue() const {
		if (mpType == Type::TYPE) {
			return mpValue;
		}
		else {
			return nullptr;
		}
	}

	Error genCode();

private:
	enum InitializerType {
		NONE,
		EXPRESSION,
		STATEMENT
	};
	std::string mName;
	const Type *mpType;
	const Type *mpValue;
	std::unique_ptr<Expression> mpTypeExpression;
	InitializerType mInitiailizerType;
	std::unique_ptr<SyntaxNode> mpInitializer;
	bool entryPoint;
};


#endif


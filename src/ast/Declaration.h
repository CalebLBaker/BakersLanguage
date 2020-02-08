#ifndef DECLARATION_H
#define DECLARATION_H


#include <memory>

#include "Error.h"
#include "Expression.h"
#include "Initializer.h"
#include "Statement.h"
#include "scan/Scanner.h"


class Declaration : public Statement {
public:

	Declaration(Scope *pScope);

	inline Declaration(std::unique_ptr<Expression>&& pType) :
		Statement(pType->scope), mpTypeExpression(std::move(pType)), mpType(nullptr),
		mpValue(nullptr)
	{}

	inline Declaration(std::string_view name, const Type *pValue, Scope *pScope) :
		Statement(pScope), mName(name), mpType(Type::TYPE), mpValue(pValue)
	{
		pScope->addVariable(this);
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
	std::unique_ptr<Expression> mpTypeExpression;
	std::string mName;
	const Type *mpType;
	const Type *mpValue;
	std::unique_ptr<Initializer> mpInitializer;
};


#endif


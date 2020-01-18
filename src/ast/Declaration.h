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

	Error parse(Scanner *pScanner);

	Error doSemanticAnalysis();

	std::string_view getName() const;

	Error genCode();

private:
	std::unique_ptr<Expression> mpType;
	std::string mName;
	std::unique_ptr<Initializer> mpInitializer;
};


#endif


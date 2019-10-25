cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0048 NEW)

project(BakersLanguage VERSION 1.0)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

add_library(blclib

	src/Error.cpp
	src/Location.cpp

	src/ast/Alias.cpp
	src/ast/ClassDeclaration.cpp
	src/ast/CompoundStatement.cpp
	src/ast/Constant.cpp
	src/ast/Declaration.cpp
	src/ast/Expression.cpp
	src/ast/ExpressionStatement.cpp
	src/ast/FunctionDeclaration.cpp
	src/ast/ParameterList.cpp
	src/ast/Pointer.cpp
	src/ast/Primitive.cpp
	src/ast/Program.cpp
	src/ast/Scope.cpp
	src/ast/Slice.cpp
	src/ast/Statement.cpp
	src/ast/SyntaxNode.cpp
	src/ast/Type.cpp
	src/ast/TypeDefinition.cpp
	src/ast/TypeModifier.cpp
	src/ast/VariableDeclaration.cpp

	src/codeGen/BasicBlock.cpp
	src/codeGen/Function.cpp
	src/codeGen/Instruction.cpp

	src/scan/Scanner.cpp
	src/scan/Token.cpp

	src/Error.h
	src/globalDefines.h
	src/Location.h

	src/ast/Alias.h
	src/ast/ClassDeclaration.h
	src/ast/CompoundStatement.h
	src/ast/Constant.h
	src/ast/Declaration.h
	src/ast/Expression.h
	src/ast/ExpressionStatement.h
	src/ast/FunctionDeclaration.h
	src/ast/ParameterList.h
	src/ast/Pointer.h
	src/ast/Primitive.h
	src/ast/Program.h
	src/ast/Scope.h
	src/ast/Slice.h
	src/ast/Statement.h
	src/ast/SyntaxNode.h
	src/ast/Type.h
	src/ast/TypeDefinition.h
	src/ast/TypeModifier.h
	src/ast/VariableDeclaration.h

	src/codeGen/BasicBlock.h
	src/codeGen/Function.h
	src/codeGen/Instruction.h
	src/codeGen/Value.h

	src/scan/Scanner.h
	src/scan/Token.h
)

set_property(TARGET blclib PROPERTY CXX_STANDARD 17)

add_executable (blc src/main.cpp)

set_property(TARGET blc PROPERTY CXX_STANDARD 17)

target_link_libraries(blc blclib)

add_subdirectory(unittests)


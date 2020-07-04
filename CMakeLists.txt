cmake_minimum_required(VERSION 3.4.3)

cmake_policy(SET CMP0048 NEW)

project(Quartz VERSION 1.0)
 
find_package(LLVM 10 EXACT REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(LLVM_ENABLE_PROJECTS "lld")
 
include_directories(${CMAKE_SOURCE_DIR}/src)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

add_library(quartzlib

	src/Error.h
	src/Location.h

	src/ast/CompoundStatement.h
	src/ast/Declaration.h
	src/ast/Expression.h
	src/ast/ExpressionStatement.h
	src/ast/FunctionType.h
	src/ast/FunctionTypeExpression.h
	src/ast/IntegerLiteral.h
	src/ast/Module.h
	src/ast/ParameterList.h
	src/ast/Primitive.h
	src/ast/Program.h
	src/ast/Scope.h
	src/ast/Statement.h
	src/ast/SyntaxNode.h
	src/ast/Type.h
	src/ast/VariableExpression.h

	src/codeGen/CodeGen.h

	src/scan/Scanner.h
	src/scan/Token.h

	src/Error.cpp
	src/Location.cpp

	src/ast/CompoundStatement.cpp
	src/ast/Declaration.cpp
	src/ast/Expression.cpp
	src/ast/ExpressionStatement.cpp
	src/ast/FunctionType.cpp
	src/ast/FunctionTypeExpression.cpp
	src/ast/IntegerLiteral.cpp
	src/ast/Module.cpp
	src/ast/ParameterList.cpp
	src/ast/Primitive.cpp
	src/ast/Program.cpp
	src/ast/Scope.cpp
	src/ast/Statement.cpp
	src/ast/SyntaxNode.cpp
	src/ast/Type.cpp
	src/ast/VariableExpression.cpp

	src/codeGen/CodeGen.cpp

	src/scan/Scanner.cpp
	src/scan/Token.cpp
)

set_property(TARGET quartzlib PROPERTY CXX_STANDARD 20)

target_link_libraries(quartzlib LLVM lldELF)

add_executable (quartzc src/main.cpp)

set_property(TARGET quartzc PROPERTY CXX_STANDARD 20)

target_link_libraries(quartzc quartzlib)


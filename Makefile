CC := g++

SOURCES := $(shell find src -name '*.cpp')
HEADERS := $(shell find src -name '*.h')
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(SOURCES))
DBGOBJECTS := $(patsubst src/%.cpp, build/debug/%.o, $(SOURCES))
COMPILERFLAGS := -c --std=c++17
INCLUDEPATH := -Isrc

all: blc

build:
	mkdir -p build
	mkdir -p build/scan
	mkdir -p build/ast
	mkdir -p build/codeGen

build/debug: build
	mkdir -p build/debug
	mkdir -p build/debug/scan
	mkdir -p build/debug/ast
	mkdir -p build/debug/codeGen

build/debug/scan/%.o: src/scan/%.cpp build/debug ${HEADERS}
	${CC} -g -Isrc -Isrc/scan ${COMPILERFLAGS} $< -o $@

build/debug/ast/%.o: src/ast/%.cpp build/debug ${HEADERS}
	${CC} -g -Isrc -Isrc/ast ${COMPILERFLAGS} $< -o $@

build/debug/codeGen/%.o: src/codeGen/%.cpp build/debug ${HEADERS}
	${CC} -g -Isrc -Isrc/codeGen ${COMPILERFLAGS} $< -o $@

build/debug/%.o: src/%.cpp build/debug ${HEADERS}
	${CC} -g -Isrc ${COMPILERFLAGS} $< -o $@

blc.dbg: $(DBGOBJECTS)
	${CC} -g $^ -o $@

build/scan/%.o: src/scan/%.cpp build ${HEADERS}
	${CC} -Isrc -Isrc/scan -O3 ${COMPILERFLAGS} $< -o $@

build/ast/%.o: src/ast/%.cpp build ${HEADERS}
	${CC} -Isrc -Isrc/ast -O3 ${COMPILERFLAGS} $< -o $@

build/codeGen/%.o: src/codeGen/%.cpp build ${HEADERS}
	${CC} -Isrc -Isrc/codeGen -O3 ${COMPILERFLAGS} $< -o $@

build/%.o: src/%.cpp build ${HEADERS}
	${CC} -Isrc -O3 ${COMPILERFLAGS} $< -o $@

blc: $(OBJECTS)
	${CC} $^ -o $@

clean:
	rm -rf build
	rm -f blc
	rm -f blc.dbg
	rm -f out.s
	rm -f out.elf


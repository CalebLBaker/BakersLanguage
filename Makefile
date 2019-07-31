CC := g++

SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(SOURCES))
DBGOBJECTS := $(patsubst src/%.cpp, build/debug/%.o, $(SOURCES))
INCLUDEPATH := -Isrc

all: blc

build:
	mkdir build
	mkdir build/scan
	mkdir build/parse

build/debug: build
	mkdir build/debug
	mkdir build/debug/scan
	mkdir build/debug/parse

build/debug/scan/%.o: src/scan/%.cpp build/debug
	${CC} -g -Isrc -Isrc/scan -c $< -o $@

build/debug/parse/%.o: src/parse/%.cpp build/debug
	${CC} -g -Isrc -Isrc/parse -c $< -o $@

build/debug/%.o: src/%.cpp build/debug
	${CC} -g -Isrc -c $< -o $@

blc.dbg: $(DBGOBJECTS)
	${CC} -g $^ -o $@

build/scan/%.o: src/scan/%.cpp build
	${CC} -Isrc -Isrc/scan -c $< -o $@

build/parse/%.o: src/parse/%.cpp build
	${CC} -Isrc -Isrc/parse -c $< -o $@

build/%.o: src/%.cpp build
	${CC} -Isrc -c $< -o $@

blc: $(OBJECTS)
	${CC} $^ -o $@

clean:
	rm -rf build
	rm -f blc
	rm -f blc.dbg


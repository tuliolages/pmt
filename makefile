CC=g++
SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))

all: pmt

pmt: $(OBJ)
	@mkdir -p bin
	g++ $(OBJ) -o bin/pmt

$(OBJ): $(SRC)
	@mkdir -p $(@D)
	g++ -std=c++11 -c $(patsubst obj/%.o, src/%.cpp, $@) -o $@

buildtest: tests/tests.cpp
	@mkdir -p bin
	g++ tests/tests.cpp -o bin/tests

runTests: buildtest pmt
	./bin/tests $(args)

run: pmt
	./bin/pmt $(args)

clean:
	rm -rf obj/*

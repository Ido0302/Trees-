# Functional Makefile for the project
# Containing: all, test, valgrind, clean
#			- all: compiles the demo and runs it
#			- test: compiles the test and runs it
#			- valgrind: runs the demo with valgrind
#			- clean: removes all object files and executables


CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I.
#GUIFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS = -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system

VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES_DEMO = Tree.hpp Node.hpp Demo.cpp
SOURCES_TEST = Tree.hpp Node.hpp Test.cpp TestCounter.cpp

tree: demo
	./demo

demo: Demo.o Tree.o Node.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: Test.o TestCounter.o Tree.o Node.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	./test

valgrind: demo
	valgrind $(VALGRIND_FLAGS) ./demo
	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test

.PHONY: all test clean valgrind
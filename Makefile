MAIN = main.o
BENCHMARK = benchmark.o
DEFINES = NONE # TEST to see function calls
CXX = g++
CXXFLAGS = -std=c++14 -Iinclude -D $(DEFINES) -Wall -Wextra

#INC = include/BST.h include/iterators.h include/myfun.h include/node.h


# eliminate default suffixes
.SUFFIXES:
SUFFIXES=

# just consider our own suffixes
.SUFFIXES: .cc .o

all: $(MAIN) $(BENCHMARK)

.PHONY: all

documentation: Doxygen/doxy.in
	doxygen $^

$(MAIN): src/main.cc 
	$(CXX) -g $< -o $(MAIN) $(CXXFLAGS)

$(BENCHMARK): src/benchmark.cc 
	$(CXX) -g $< -o $(BENCHMARK) $(CXXFLAGS)

clean:
	rm -rf *.o html latex

.PHONY: clean

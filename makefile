WARNINGS = -Wall -Wextra -Wno-missing-field-initializers -Wno-sign-compare -Wno-unused-variable -Wno-switch
STD = -std=c++1y
OPTIMIZE = -O3

CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

CXX=g++-5

all: calc

debug: OPTIMIZE = -Og -g
debug: calc

calc: $(OBJ_FILES)
	@echo Linking $@
	@$(CXX) $(STD) -o $@ $^

bin/%.o: src/%.cpp
	@mkdir -p bin/
	@echo CXX $@
	@$(CXX) $(STD) $(WARNINGS) $(OPTIMIZE) -c -o $@ $<

clean:
	rm -f bin/*.o
	rm -f calc

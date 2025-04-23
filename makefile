CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wmissing-include-dirs -Wunused-value -std=c++17 -I./include -g -Og

LDFLAGS = -L./libs/SFML/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
OUT = ./bin/game1.exe

all: $(OUT)

# Build executable
$(OUT): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(OUT)


# Build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

remove-obj:
	rm -f $(OBJ)

remove-out:
	rm -f $(OUT)

clean:
	make remove-obj && make remove-out

compiledb
compiledb make

create-format
clang-format -style=LLVM -dump-config > .clang-format

rebuild: clean all remove-obj
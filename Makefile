# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall

# Include directories
INCLUDES = -I"Assignment 1" -I"Assignment 2/include"

# Assignment 1 sources
A1_SRC = \
"Assignment 1/driver.cpp" \
"Assignment 1/simple_gemm.cpp" \
"Assignment 1/blocked_gemm.cpp"

# Assignment 2 sources
A2_SRC = \
"Assignment 2/src/driver.cpp" \
"Assignment 2/src/graph.cpp" \
"Assignment 2/src/csr.cpp" \
"Assignment 2/src/bellman_ford.cpp" \
"Assignment 2/src/floyd_warshall.cpp"

# Wrapper source
MAIN = main.cpp

# All sources
SRC = $(MAIN) $(A1_SRC) $(A2_SRC)

# Executable
TARGET = cs509

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all
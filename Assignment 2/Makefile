# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Include folder
INC = -Iinclude

# Source files
SRC = src/driver.cpp \
      src/graph.cpp \
      src/csr.cpp \
      src/bellman_ford.cpp \
      src/floyd_warshall.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable
TARGET = assignment2

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# Remove generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Rebuild project
rebuild: clean all
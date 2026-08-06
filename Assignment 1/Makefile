CXX = g++

CXXFLAGS = -std=c++17 -Wall -O2

TARGET = gemm

SRC = driver.cpp simple_gemm.cpp blocked_gemm.cpp

OBJ = $(SRC:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp gemm.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all
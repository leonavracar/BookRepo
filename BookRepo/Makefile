CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O0 -Iinclude

MAIN = src/main.cpp
LIB_SRC = $(wildcard lib/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)
SRC_OBJ = src/Menu.o src/utils.o

all: app

app: $(MAIN) $(LIB_OBJ) $(SRC_OBJ)
	$(CXX) $(CXXFLAGS) $(MAIN) $(LIB_OBJ) $(SRC_OBJ) -o app

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f lib/*.o src/*.o app

run: app
	./app

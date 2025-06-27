CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lncurses

SRC = main.cpp SnakeGame.cpp 
OBJ = $(SRC:.cpp=.o)
TARGET = snake_game

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)


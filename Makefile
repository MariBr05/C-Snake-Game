CXX = g++						#the compiler we want to use 
CXXFLAGS = -std=c++17 -Wall		#the flags, use the lates version of c++ and -wall which will help us debug
LDFLAGS = -lncurses

SRC = main.cpp SnakeGame.cpp 	#source code
OBJ = $(SRC:.cpp=.o)			#create object files
TARGET = snake_game				#name of executable

$(TARGET): $(OBJ)				#link object files to executable 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp						#compile the object files
	$(CXX) $(CXXFLAGS) -c $<	

clean:							#clean out the object files
	rm -f $(OBJ) $(TARGET)


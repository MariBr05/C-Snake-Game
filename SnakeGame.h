#include <iostream>
#include <vector>
using namespace std;

class SnakeGame{
    private:

    bool gameOver;              //whether the game is done or not
    int height, width;          //board proportions 
    
    int snakeHeadX, snakeHeadY; //location of snake
    int foodX, foodY;           //location of food (maybe implement as vectors to have more than 1 at a time)

    int score;

    //to be implemented later
    vector <int> snakeTailX, snakeTailY;
    int tailLength;

    enum eDirection{
        STOP = 0,
        LEFT,
        RIGHT,
        UP, 
        DOWN
    };

    eDirection dir;

    public:

    bool isGameOver(){return gameOver;}

    void Setup();//
    void Print();//print the board
    void Input();//read input
    void Logic();//check the rules
    void Start();


};
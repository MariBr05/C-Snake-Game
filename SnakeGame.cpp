#include "SnakeGame.h"
#include <ncurses.h>
#include <algorithm>


SnakeGame :: SnakeGame(){
    initscr();              // Start ncurses
    noecho();               // Don't echo typed characters
    curs_set(FALSE);        // Hide cursor
    keypad(stdscr, TRUE);   // Tells the computer to be prepared for any actions like using the arrow keys
    halfdelay(1);           // Determines the speed of the game, you press a key once and the snake keeps moving on that direction
    clear();                // Clear the screen

    gameOver = false;
    score = 0;

    //make this more better
    width = 20;
    height = 12;

    dir = STOP;

    //snake is going to start in the middle of the board
    snakeHeadX = width/2;
    snakeHeadY = height/2;

    //food is going to spawn in random places everytime
    srand(time(NULL));
    foodX = rand() % width;
    foodY = rand() % height;

    //for the vectors (later)
    tailLength = 0;
    snakeTailX.resize(100);
    snakeTailY.resize(100);

    Start();
}

//for print, since we are using ncurse you cant just use cout, must use ncurses own fucntions
void SnakeGame :: Print(){

    
    clear(); // for clearing the screen before every call

    //#########
    //#       #
    //#       #
    //#       #
    //#########

    //top border
    for(int i = 0; i < width + 2; i++)
        mvaddch(0, i, '#');;
    cout<< endl;

    // grid rows
    for (int j = 0; j < height; j++) {
        mvaddch(j + 1, 0, '#'); // left border
        for (int k = 0; k < width; k++) {
            if (snakeHeadX == k && snakeHeadY == j)
                mvaddch(j + 1, k + 1, '5');  // snake head
            else if (foodX == k && foodY == j)
                mvaddch(j + 1, k + 1, '%');  // food
            else
            {
                int printed = false; 
                for(int t = 0; t < tailLength; t++)
                {
                    if(snakeTailX[t] == k && snakeTailY[t] == j){
                        mvaddch(j + 1, k + 1, 'o');
                        //mvprintw (j+1, k+1, "%c", 'o');
                        printed = true;
                        break;
                    }  
                } 

                if(!printed)
                    mvaddch(j + 1, k + 1, ' ');  // empty        
            }
        }
        mvaddch(j + 1, width + 1, '#'); // right border
    }

    // bottom border
    for (int i = 0; i < width + 2; i++)
        mvaddch(height + 1, i, '#');

    mvprintw (height + 3, 1, "Score: %d", score);
    refresh(); // push updates to the screen
}

void SnakeGame :: Input(){
    
    int ch = getch();

    if(ch != ERR){
        switch(ch){
            case KEY_LEFT:
                dir = LEFT;
                break;
            case KEY_RIGHT:
                dir = RIGHT;
                break;
            case KEY_UP:
                dir = UP;
                break;
            case KEY_DOWN:
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }//end if
}// end input 

void SnakeGame :: Logic(){

    int prevTailX = snakeTailX[0];
    int prevTailY = snakeTailY[0];

    //Before moving the tail segements, we first assign the previous 
    //head position to the first tail segment 
    snakeTailX[0] = snakeHeadX;  
    snakeTailY[0] = snakeHeadY;  

    int prev2X, prev2Y;

    //shifting all tail segments once we move
    for(int i = 1; i < tailLength; i++){
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];

        snakeTailX[i] = prevTailX;
        snakeTailY[i] = prevTailY;

        prevTailX = prev2X;
        prevTailY = prev2Y;
    }

    switch(dir){
        case LEFT:
            snakeHeadX--;
            break;
        case RIGHT:
            snakeHeadX++;
            break;
        case UP:
            snakeHeadY--;
            break;
        case DOWN:
            snakeHeadY++;
            break;
        default:
            break;
    }

    //walls ( easy )
    if(snakeHeadX >= width)
        snakeHeadX = 0;
    else if (snakeHeadX < 0)
        snakeHeadX = width -1;

    if(snakeHeadY >= height)
        snakeHeadY = 0;
    else if (snakeHeadY < 0)
        snakeHeadY = height -1;
    
    //walls hard
    // if (snakeHeadX > width || snakeHeadX < 0||snakeHeadY > height||snakeHeadY < 0)
    //     gameOver = true;

    //eating the food
    if(snakeHeadX == foodX && snakeHeadY == foodY){
        score++;

        //regenerate the food
        srand(time(NULL));
        foodX = rand() % width;
        foodY = rand() % height;

        tailLength++;
    }

    //hitting itself (gameOver)
    for(int t = 0; t < tailLength; t++){
        if (snakeHeadX == snakeTailX[t] && snakeHeadY == snakeTailY[t])
            gameOver = true;
    }

}


void SnakeGame :: Start(){
   
    while(!gameOver){
        Print();
        
        Input();

        Logic();
    }

    endwin(); //exit ncurses
}
#ifndef BOARD_H 
#define BOARD_H 

class Board
{
private:
    int** panel; 
    int numRows; 
    int numCols;
    int target; // what is the goal
    int max; // the current max in all cells of panel

    void allocateMemory(); // apply dynamic memory for panel
    void clear(); // set each cell of the panel to be zero
    void updateMax(); // update the max value in the board

public:
    Board(); // construct a 3 x 3 panel
    Board(int m); // construct a m x m panel
    Board(int m, int n); // construct a m x n panel
    ~Board(); // destructor, release dynamic memory
    void setGoal(int goal); // set goal of the game
    void print() const; // print the panel
    void selectRandomCell(int& row, int& col); // select a random cell from empty cell
    void pressUp();
    void pressDown();
    void pressLeft();
    void pressRight(); // press right key
    void start(); // start the game
    bool noAdjacentSameValue() const; // check for no adjacent cells with the same value
};

#endif // BOARD_H

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
using namespace std;

class Board
{
private:
    // 2D array to display hidden and revealed cells
    char board[9][9];

    // 2D vector to store mine positions
    // 1 = Mine, 0 = Safe cell
    vector<vector<int>> mineBoard;

    // Count mines around a selected cell
    int countAdjacentMines(int row, int col);

    // Place 10 random mines
    void placeMines();

public:
    // Constructor
    Board();

    // Initialize the board
    void resetBoard();

    // Display the board
    void displayBoard();

    // Reveal a selected cell
    // Returns false if the cell contains a mine
    bool revealCell(int row, int col);

    // Count revealed safe cells
    int getRevealedSafeCount();
};

#endif

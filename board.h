#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
using namespace std;

class Board
{
private:
    // 2D array to store hidden and revealed cells
    char board[9][9];

    // 2D vector to store mine positions
    // 1 = Mine, 0 = Safe cell
    vector<vector<int>> mineBoard;

    // 2D array to store flags
    bool flagged[9][9];

    int countAdjacentMines(int row, int col);
    void placeMines();

    // Automatically reveal neighboring safe cells
    void floodReveal(int row, int col);

public:
    Board();

    void resetBoard();

    // Display board; showMines is true after Game Over
    void displayBoard(bool showMines = false);

    bool revealCell(int row, int col);

    // Place or remove a flag
    bool toggleFlag(int row, int col);

    // Get information about cells
    char getCell(int row, int col);
    bool isMine(int row, int col);
    bool isFlagged(int row, int col);

    // Get game counters
    int getRevealedSafeCount();
    int getFlagCount();
    int getRemainingSafeCells();
};

#endif
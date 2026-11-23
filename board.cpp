#include "board.h"
#include <cstdlib>
#include <ctime>
//constractor
Board::Board()
{
    // Seed random numbers only once
    static bool seeded = false;

    if (!seeded)
    {
        srand(time(0));
        seeded = true;
    }

    resetBoard();
}

// Initialize the board
void Board::resetBoard()
{
    // Initialize the 2D array with hidden cells
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = '?';
        }
    }

    // Initialize the 2D vector with zeros
    mineBoard.assign(9, vector<int>(9, 0));

    // Place 10 random mines
    placeMines();
}

// Place exactly 10 random mines
void Board::placeMines()
{
    int count = 0;

    while (count < 10)
    {
        int row = rand() % 9;
        int col = rand() % 9;

        // Check that the cell does not already contain a mine
        if (mineBoard[row][col] == 0)
        {
            mineBoard[row][col] = 1;
            count++;
        }
    }
}

// Count mines in the eight neighboring cells
int Board::countAdjacentMines(int row, int col)
{
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int newRow = row + i;
            int newCol = col + j;

            // Check board boundaries
            if (newRow >= 0 && newRow < 9 &&
                newCol >= 0 && newCol < 9)
            {
                if (mineBoard[newRow][newCol] == 1)
                {
                    count++;
                }
            }
        }
    }

    return count;
}

// Display the game board
void Board::displayBoard()
{
    cout << "\n    ";

    // Display column numbers
    for (int j = 0; j < 9; j++)
    {
        cout << j << " ";
    }

    cout << endl;

    // Display rows and cells
    for (int i = 0; i < 9; i++)
    {
        cout << i << " | ";

        for (int j = 0; j < 9; j++)
        {
            cout << board[i][j] << " ";
        }

        cout << endl;
    }
}

// Reveal a selected cell
bool Board::revealCell(int row, int col)
{
    // Check valid row and column
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return false;
    }

    // Check if selected cell contains a mine
    if (mineBoard[row][col] == 1)
    {
        return false;
    }

    // Count nearby mines and reveal the number
    int mines = countAdjacentMines(row, col);

    board[row][col] = '0' + mines;

    return true;
}

// Count all revealed safe cells
int Board::getRevealedSafeCount()
{
    int count = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '?' && mineBoard[i][j] == 0)
            {
                count++;
            }
        }
    }

    return count;
}

#include "board.h"
#include <cstdlib>
#include <ctime>

// Constructor
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
    // Initialize the 2D array and flags
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = '?';
            flagged[i][j] = false;
        }
    }

    // Initialize the 2D vector
    mineBoard.assign(9, vector<int>(9, 0));

    // Place exactly 10 mines
    placeMines();
}

// Place 10 random mines
void Board::placeMines()
{
    int count = 0;

    while (count < 10)
    {
        int row = rand() % 9;
        int col = rand() % 9;

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

// Display the board
void Board::displayBoard(bool showMines)
{
    cout << "\n    ";

    for (int j = 0; j < 9; j++)
    {
        cout << j << " ";
    }

    cout << endl;

    for (int i = 0; i < 9; i++)
    {
        cout << i << " | ";

        for (int j = 0; j < 9; j++)
        {
            if (showMines && mineBoard[i][j] == 1)
            {
                cout << "* ";
            }
            else if (flagged[i][j])
            {
                cout << "F ";
            }
            else
            {
                cout << board[i][j] << " ";
            }
        }

        cout << endl;
    }
}

// Automatically reveal safe neighboring cells
void Board::floodReveal(int row, int col)
{
    // Stop if outside the board
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return;
    }

    // Stop if already revealed or flagged
    if (board[row][col] != '?' || flagged[row][col])
    {
        return;
    }

    // Never reveal a mine through this function
    if (mineBoard[row][col] == 1)
    {
        return;
    }

    // Count nearby mines and reveal the cell
    int mines = countAdjacentMines(row, col);
    board[row][col] = '0' + mines;

    // If there are no nearby mines, reveal neighbors too
    if (mines == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    floodReveal(row + i, col + j);
                }
            }
        }
    }
}

// Reveal a selected cell
bool Board::revealCell(int row, int col)
{
    // Check valid position
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return false;
    }

    // Do not reveal a flagged cell
    if (flagged[row][col])
    {
        return true;
    }

    // Check if selected cell is a mine
    if (mineBoard[row][col] == 1)
    {
        return false;
    }

    // Automatically reveal neighboring safe cells if possible
    floodReveal(row, col);

    return true;
}

// Place or remove a flag
bool Board::toggleFlag(int row, int col)
{
    // Check valid position
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return false;
    }

    // A revealed cell cannot be flagged
    if (board[row][col] != '?')
    {
        return false;
    }

    // Change flag status
    flagged[row][col] = !flagged[row][col];

    return true;
}

// Get the value of a cell
char Board::getCell(int row, int col)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return '?';
    }

    return board[row][col];
}

// Check whether a cell contains a mine
bool Board::isMine(int row, int col)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return false;
    }

    return mineBoard[row][col] == 1;
}

// Check whether a cell is flagged
bool Board::isFlagged(int row, int col)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9)
    {
        return false;
    }

    return flagged[row][col];
}

// Count revealed safe cells
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

// Count placed flags
int Board::getFlagCount()
{
    int count = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (flagged[i][j])
            {
                count++;
            }
        }
    }

    return count;
}

// Count remaining hidden safe cells
int Board::getRemainingSafeCells()
{
    return 81 - 10 - getRevealedSafeCount();
}
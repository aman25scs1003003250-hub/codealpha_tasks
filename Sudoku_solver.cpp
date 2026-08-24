#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; ++row) {
        if (row % 3 == 0 && row != 0) {
            cout << "---------------------\n";
        }
        for (int col = 0; col < N; ++col) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }
            cout << grid[row][col] << " ";
        }
        cout << "\n";
    }
}

bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {

    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}
bool solveSudoku(vector<vector<int>>& grid) {
    int row = -1;
    int col = -1;
    bool isEmpty = false;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    if (!isEmpty) {
        return true;
    }

    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num; 

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false; 
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "=== Input Sudoku Puzzle ===\n\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\n=== Solved Sudoku Grid ===\n\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
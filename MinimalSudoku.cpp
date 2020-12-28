#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>

using namespace std;

// Sudoku game
// 9x9 represented by a array of 9 array of length 9
// difficulties: number of values deleted
// solution and then problem
// i represents row, j represents column


int grid[9][9]; // Initialize an empty grid

void grid_difficulty(int diff) {
    //easy:remove 3, 4 numbers per row, medium: remove 5, 6 per row, hard: remove 7-9 per row
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (rand() % 10 + 1 <= diff) {
                grid[i][j] = 0;
            }
        }
    }
}

void grid_print() {
    // Prints the current state of the grid
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                cout << "-";
            } else {
                cout << grid[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }
}

bool is_valid(int value, int i, int j) {
    // Return true if value is valid and false if value is not valid
    // A valid value is a value that is not present in its row, column, or 3x3 square


    int box[2][3]; // Box dimensions
    int dims[] = {i, j};
    int start_i;
    for (int k = 0; k < 2; k++) { // Find the mini grid that the value is in
        if (dims[k] <= 2) {
            start_i = 0;
        } else if (dims[k] >= 6) {
            start_i = 6;
        } else {
            start_i = 3;
        }

        for (int box_i = 0; box_i <= 2; box_i++) {
            box[k][box_i] = start_i + box_i;
        }
    }

    for (int k = 0; k < 9; k++) {
        if (grid[k][j] == value) { // Check column
            return false;
        }

        if (grid[i][k] == value) { // Check row
            return false;
        }
    }

    for (int box_i : box[0]) {
        for (int box_j : box[1]) {
            if (grid[box_i][box_j] == value) {
                return false;
            }
        }
    }

    return true;
}

void grid_clear() {
// Clears the grid with all 0s
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    }
}

void grid_fill() {
    int counter = 0;

    for (int i = 0; i < 9;) { // For each row
        int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int vals_rem = 9; vals_rem > 0; vals_rem--) { // Limiting the array to remaining
            int last = vals_rem - 1;
            int rand_i = rand() % vals_rem;
            int val = vals[rand_i]; // Choose value

            vals[rand_i] = vals[last];
            vals[last] = 0; // Discard used value

            for (int j = 0; j < 9; j++) {
                if (grid[i][j] == 0 && is_valid(val, i, j)) {
                    grid[i][j] = val;
                }
            }
        }

        if (end(grid[i]) != find(begin(grid[i]), end(grid[i]), 0)) {
            if (i == 5) {
                counter++;
                if (counter >= 9) {
                    grid_clear();
                    grid_fill(); // Recurse into grid_fill
                }
            }

            for (int j = 0; j < 9; j++) {
                grid[i][j] = 0;
            }
        } else {
            i++;
        }
    }
}

bool grid_check() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0 && !is_valid(grid[i][j], i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool grid_play() {
    while (!grid_check()) {
        int i, j, num;
        cout << "Input row, column, and value (1-9): ";
        cin >> i >> j >> num;
        if (grid[i - 1][j - 1] != 0) {
            cout << "(You are not allowed to change values)\n";
        } else if (!is_valid(num, i - 1, j - 1)) {
            grid[i - 1][j - 1] = num;
            grid_print();
            cout << "[Sudoku Failed]\n";
            return false;
        } else {
            grid[i - 1][j - 1] = num;
            grid_print();
        }
    }
    cout << "[Sudoku Complete] \n";
    return true;
}


int main() {
    srand((unsigned) time(0)); // Look into this
    grid_fill();

    int diff;
    string user_try;
    while (user_try == "y") {
        cout << "Enter an integer from 1-9 for difficulty selection: ";
        cin >> diff;
        grid_difficulty(diff);

        grid_print();
        if (grid_play()) { ;
            cout << "Completed Sudoku: Level " << diff << "!\n";
            cout << "Play again? (y/n): ";
        } else {
            cout << "Failed Sudoku: Level " << diff << "!\n";
            cout << "Play again? (y/n): ";
        }
        cin >> user_try;
    }

    return 0;
}

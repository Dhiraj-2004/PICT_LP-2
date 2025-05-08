#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N = 9;

typedef vector<vector<int>> Board;
Board fixed(N, vector<int>(N));  // Fixed clues

bool isFixed[N][N];

int getConflicts(const Board& board) {
    int conflicts = 0;

    // Row conflicts
    for (int i = 0; i < N; i++) {
        vector<int> count(N + 1, 0);
        for (int j = 0; j < N; j++)
            count[board[i][j]]++;
        for (int k = 1; k <= N; k++)
            if (count[k] > 1) conflicts += count[k] - 1;
    }

    // Column conflicts
    for (int j = 0; j < N; j++) {
        vector<int> count(N + 1, 0);
        for (int i = 0; i < N; i++)
            count[board[i][j]]++;
        for (int k = 1; k <= N; k++)
            if (count[k] > 1) conflicts += count[k] - 1;
    }

    return conflicts;
}

void fillBox(Board& board, int startRow, int startCol) {
    vector<int> nums;
    for (int i = 1; i <= 9; i++) nums.push_back(i);

    // Remove fixed numbers
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            int r = startRow + i;
            int c = startCol + j;
            if (isFixed[r][c]) nums.erase(remove(nums.begin(), nums.end(), board[r][c]), nums.end());
        }

    // Shuffle remaining and place
    random_shuffle(nums.begin(), nums.end());
    int index = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            int r = startRow + i;
            int c = startCol + j;
            if (!isFixed[r][c]) board[r][c] = nums[index++];
        }
}

void initialize(Board& board) {
    // Fill each 3x3 box
    for (int i = 0; i < N; i += 3)
        for (int j = 0; j < N; j += 3)
            fillBox(board, i, j);
}

bool hillClimb(Board& board) {
    int currentConflicts = getConflicts(board);
    bool improved = false;

    for (int boxRow = 0; boxRow < 3; boxRow++) {
        for (int boxCol = 0; boxCol < 3; boxCol++) {
            vector<pair<int, int>> cells;

            // Collect non-fixed cells in this 3x3 box
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    int r = boxRow * 3 + i;
                    int c = boxCol * 3 + j;
                    if (!isFixed[r][c])
                        cells.emplace_back(r, c);
                }

            // Try all swaps
            for (size_t a = 0; a < cells.size(); a++) {
                for (size_t b = a + 1; b < cells.size(); b++) {
                    swap(board[cells[a].first][cells[a].second], board[cells[b].first][cells[b].second]);
                    int newConflicts = getConflicts(board);

                    if (newConflicts < currentConflicts) {
                        currentConflicts = newConflicts;
                        improved = true;
                    } else {
                        // Revert swap
                        swap(board[cells[a].first][cells[a].second], board[cells[b].first][cells[b].second]);
                    }
                }
            }
        }
    }

    return improved;
}

void printBoard(const Board& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    srand(time(0));

    // Example puzzle with some fixed values
    Board board = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };

    // Mark fixed cells
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            isFixed[i][j] = (board[i][j] != 0);

    initialize(board);

    int steps = 0;
    while (hillClimb(board) && steps < 10000) {
        steps++;
    }

    cout << "Solved Sudoku (or local optimum):\n";
    printBoard(board);
    cout << "Total Conflicts: " << getConflicts(board) << "\n";
    cout << "Steps taken: " << steps << "\n";

    return 0;
}

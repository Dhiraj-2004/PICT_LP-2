#include <iostream>
#include <vector>
using namespace std;

class NQueenSolver {
private:
    int N;
    vector<bool> leftRow;
    vector<bool> upperDiagonal;
    vector<bool> lowerDiagonal;
    vector<vector<int>> board;

public:
    NQueenSolver(int size) {
        N = size;
        board = vector<vector<int>>(N, vector<int>(N, 0));
        leftRow = vector<bool>(N, false);
        upperDiagonal = vector<bool>(2 * N - 1, false);
        lowerDiagonal = vector<bool>(2 * N - 1, false);
    }

    void printBoard() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] == 1 ? "Q " : ". ");
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool solve(int col) {
        if (col >= N)
            return true;

        for (int row = 0; row < N; row++) {
            if (!leftRow[row] && !lowerDiagonal[row + col] && !upperDiagonal[N - 1 + col - row]) {
                board[row][col] = 1;
                leftRow[row] = lowerDiagonal[row + col] = upperDiagonal[N - 1 + col - row] = true;

                if (solve(col + 1))
                    return true;

                // Backtrack
                board[row][col] = 0;
                leftRow[row] = lowerDiagonal[row + col] = upperDiagonal[N - 1 + col - row] = false;
            }
        }

        return false;
    }

    void solveNQueens() {
        if (solve(0)) {
            cout << "One of the possible solutions:\n";
            printBoard();
        } else {
            cout << "No solution exists for N = " << N << "\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter number of rows/columns (N): ";
    cin >> n;

    if (n < 1) {
        cout << "Invalid board size. Must be >= 1.\n";
        return 1;
    }

    NQueenSolver solver(n);
    solver.solveNQueens();

    return 0;
}

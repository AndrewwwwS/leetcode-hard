#include <iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>
#include<array>
#include <bitset>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        rows.fill(0);
        cols.fill(0);
        blocks.fill(0);
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] != '.') {
                    int num = board[row][col] - '1';
                    placeNumber(board, row, col, num);
                }
            }
        }
        backtrack(board, 0, 0);
    }

private:
    array<bitset<9>, 9> rows, cols, blocks;
    void placeNumber(vector<vector<char>>& board, int row, int col, int num) {
        board[row][col] = num + '1';
        rows[row].set(num);
        cols[col].set(num);
        blocks[3 * (row / 3) + col / 3].set(num);
    }
    void removeNumber(vector<vector<char>>& board, int row, int col, int num) {
        board[row][col] = '.';
        rows[row].reset(num);
        cols[col].reset(num);
        blocks[3 * (row / 3) + col / 3].reset(num);
    }
    bool couldPlace(int row, int col, int num) const {
        int blockIndex = 3 * (row / 3) + col / 3;
        return !rows[row][num] && !cols[col][num] && !blocks[blockIndex][num];
    }
    bool backtrack(vector<vector<char>>& board, int row, int col) {
        if (row == 9) return true;
        if (col == 9) return backtrack(board, row + 1, 0);
        if (board[row][col] != '.') return backtrack(board, row, col + 1);
        for (int num = 0; num < 9; ++num) {
            if (couldPlace(row, col, num)) {
                placeNumber(board, row, col, num);
                if (backtrack(board, row, col + 1)) return true;
                removeNumber(board, row, col, num);
            }
        }
        return false;
    }
};

int main() {
    Solution solution;
    vector<vector<char>> board = 
        {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    solution.solveSudoku(board);
    cout << "Solution:" << endl;
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }
    return 0;
}
#include <math.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
inline int two(int n) {
    return 1 << n;
}
inline int test(int n, int b) {
    return (n >> b) & 1;
}
inline void set_bit(int& n, int b) {
    n |= two(b);
}
inline void unset_bit(int& n, int b) {
    n &= ~two(b);
}
inline int last_bit(int n) {
    return n & (-n);
}
inline int ones(int n) {
    int res = 0;
    while (n && ++res)
        n -= n & (-n);
    return res;
}
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}
template <typename T>
inline void showMatrix(std::vector<std::vector<T>>& m) {
    for (std::vector<T>& l : m) {
        for (T& t : l) {
            std::cout << t << ' ';
        }
        std::cout << '\n';
    }
}
/////////////////////////////////////////////////////////////
using namespace std;

/*
Eight Queens: Write an algorithm to print all ways of arranging
eight queens on an 8x8 chess board so that none of them
share the same row, column, or diagonal. In this case, "diagonal"
means all diagonals, not just the two that bisect the board.
*/

vector<vector<int>> buildChessBoard(const int& width = 8) {
    return vector<vector<int>>(width, vector<int>(width, -1));
}

void mark(vector<vector<int>>& board, const int& r, const int& c) {
    int len = board.size();
    for (int i = 0; i < len; ++i) {
        board[i][c] = 1;
        board[r][i] = 1;
    }

    // figure out diagnal starting points
    int dr1 = (r > c) ? (r - c) : (0);
    int dc1 = (r > c) ? (0) : (c - r);
    int dr2 = r, dc2 = c;
    while (dr2 != 0 and dc2 < len - 1) {
        dr2--;
        dc2++;
    }

    // mark diagnals
    while (dr1 < len and dc1 < len) {
        board[dr1++][dc1++] = 1;
    }
    while (dr2 < len and dc2 >= 0) {
        board[dr2++][dc2--] = 1;
    }

    board[r][c] = 0;
}

int solution_count = 1;

void eightQueens(vector<vector<int>>& chessBoard, const int& row) {
    if (row == chessBoard.size()) {
        cout << "solution #" << solution_count << '\n';
        showMatrix<int>(chessBoard);
        cout << "\n";
        solution_count++;
        return;
    }

    for (int i = 0; i < chessBoard.size(); ++i) {
        vector<vector<int>> saveboard = chessBoard;
        if (chessBoard[row][i] != 1) {
            mark(saveboard, row, i);
            eightQueens(saveboard, row + 1);
        }
    }
}

int main() {
    const int board_w = 8;
    auto chessBoard = buildChessBoard(board_w);
    eightQueens(chessBoard, 0);  // doesn's necessarily be 8
    // this function tries to place 0 in each row

    return 0;
}

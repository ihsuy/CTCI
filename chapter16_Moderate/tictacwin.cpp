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

/////////////////////////////////////////////////////////////
using namespace std;

/*
Tic Tac Win: Design an algorithm to figure out
if someone has won a game of tic-tac-toe.
*/

char tictacWin_3x3_naive(
    const vector<vector<char>>&
        grid) {  // return winner's mark: 2 players: 'O' and 'X'
    // if no winner return 'N'
    // on our board, empty locations are marked with ' '(white space)

    if (grid.size() != 3 or grid[0].size() != 3) {
        throw runtime_error("tictacWin_3x3 only accepts 3x3 grids");
    }

    // check every row
    for (int r = 0; r < 3; ++r) {
        int o_count = 0, x_count = 0;

        for (int c = 0; c < 3; c++) {
            char val = grid[r][c];

            if (val == 'O') {
                o_count++;
            } else if (val == 'X') {
                x_count++;
            } else {
                break;
            }
        }

        if (o_count == 3 or x_count == 3) {
            return (o_count == 3) ? 'O' : 'X';
        }
    }

    // check every col
    for (int c = 0; c < 3; ++c) {
        int o_count = 0, x_count = 0;

        for (int r = 0; r < 3; r++) {
            char val = grid[r][c];

            if (val == 'O') {
                o_count++;
            } else if (val == 'X') {
                x_count++;
            } else {
                break;
            }
        }

        if (o_count == 3 or x_count == 3) {
            return (o_count == 3) ? 'O' : 'X';
        }
    }

    // check diagonals
    int o_count1 = 0, x_count1 = 0, o_count2 = 0, x_count2 = 0;
    for (int d = 0; d < 3; ++d) {
        char val1 = grid[d][d];

        if (val1 == 'X') {
            x_count1++;
        } else if (val1 == 'O') {
            o_count1++;
        }

        char val2 = grid[d][2 - d];

        if (val2 == 'X') {
            x_count2++;
        } else if (val2 == 'O') {
            o_count2++;
        }
    }

    if (x_count1 == 3 or o_count1 == 3 or x_count2 == 3 or o_count2 == 3) {
        return (x_count1 == 3 or x_count2 == 3) ? 'X' : 'O';
    }

    return 'N';
}

bool threeEqual(const char& c1, const char& c2, const char& c3) {
    if (c1 == ' ' or c2 == ' ' or c3 == ' ') {
        return false;
    }

    return (c1 == c2) and (c2 == c3);
}

char tictacWin_3x3_cleaner(const vector<vector<char>>& grid) {
    // check rows & columns
    for (int i = 0; i < 3; ++i) {
        if (threeEqual(grid[i][0], grid[i][1], grid[i][2])) {
            return grid[i][0];
        }

        if (threeEqual(grid[0][i], grid[1][i], grid[2][i])) {
            return grid[0][i];
        }
    }

    if (threeEqual(grid[0][0], grid[1][1], grid[2][2]) or
        threeEqual(
            grid[0][2], grid[1][1],
            grid[2][0])) {  // since two diagonals intersect at grid[1][1]
        return grid[1][1];
    }

    return 'N';
}

bool rowCompleted(const vector<vector<char>>& grid,
                  const int& r,
                  const int& width) {
    for (int i = 1; i < width; ++i) {
        char first = grid[r][i - 1];

        if ((first == ' ') or (grid[r][i] != first)) {
            return false;
        }
    }
    return true;
}

bool colCompleted(const vector<vector<char>>& grid,
                  const int& c,
                  const int& width) {
    for (int i = 1; i < width; ++i) {
        char first = grid[i - 1][c];

        if ((first == ' ') or (grid[i][c] != first)) {
            return false;
        }
    }
    return true;
}

int diagCompleted(const vector<vector<char>>& grid, const int& width) {
    bool d1_completed = true, d2_completed = true;

    for (int i = 1; i < width; ++i) {
        char first1 = grid[i - 1][i - 1];
        char first2 = grid[i - 1][width - i];

        if ((first1 == ' ') or (grid[i][i] != first1)) {
            d1_completed = false;
        }

        if ((first2 == ' ') or (grid[i][width - 1 - i] != first2)) {
            d2_completed = false;
        }
    }

    return (d1_completed) ? 0 : ((d2_completed) ? width - 1 : -1);
}

char tictacWin_nxn(const vector<vector<char>>& grid) {
    if (grid.size() != grid[0].size()) {
        throw runtime_error("invalid grid size");
    }

    int width = grid.size();

    for (int i = 0; i < width; ++i) {
        if (rowCompleted(grid, i, width)) {
            return grid[i][0];
        }

        if (colCompleted(grid, i, width)) {
            return grid[0][i];
        }
    }

    int completed_d = diagCompleted(grid, width);

    if (completed_d != -1) {
        return grid[0][completed_d];
    }

    return 'N';
}

int main() {
    vector<vector<char>> grid{
        {'O', 'X', 'X'}, {'X', 'O', 'O'}, {'X', 'O', 'X'}};

    vector<vector<char>> larger_grid{
        {' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'O'},
        {' ', ' ', ' ', ' ', ' ', 'X', ' ', 'O', ' '},
        {'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O'},
        {' ', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'O', 'X', ' ', ' ', ' '},
        {' ', ' ', ' ', 'O', ' ', 'X', ' ', ' ', ' '},
        {' ', ' ', 'O', ' ', ' ', 'X', ' ', ' ', ' '},
        {' ', 'O', ' ', ' ', ' ', 'X', ' ', ' ', ' '},
        {'O', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' '},
    };

    cout << "winner: " << tictacWin_3x3_naive(grid) << endl;
    cout << "winner: " << tictacWin_3x3_cleaner(grid) << endl;
    cout << "winner: " << tictacWin_nxn(larger_grid) << endl;
    return 0;
}

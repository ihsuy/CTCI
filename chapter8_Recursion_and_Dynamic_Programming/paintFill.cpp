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
Paint Fill: Implement the "paint nil" function that one might
see on many image editing programs. That is, given a screen
(represented by a two-dimensional array of colors), a point,
and a new color, fill in the surrounding area until the color
changes from the original color.
*/

const vector<int> directions{1, 0, -1, 0, 1};

void paintFill(vector<vector<int>>& paint,
               const int& r,
               const int& c,
               const int& color) {
    int current_color = paint[r][c];  // record prev color
    paint[r][c] = color;              // fill with color

    for (int i = 0; i < 4; ++i) {
        int r1 = r + directions[i];
        int c1 = c + directions[i + 1];

        // look for all prev colors
        if (r1 >= 0 and c1 >= 0 and r1 < paint.size() and
            c1 < paint[0].size() and paint[r1][c1] == current_color) {
            paintFill(paint, r1, c1, color);
        }
    }
}

int main() {
    vector<vector<int>> paint{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                              {1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1},
                              {2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2},
                              {2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1},
                              {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1},
                              {1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1},
                              {1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1},
                              {1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1},
                              {1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                              {1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1},
                              {2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2},
                              {2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1},
                              {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1},
                              {1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1},
                              {1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1},
                              {1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1}};

    paintFill(paint, 2, 0, 0);

    for (auto& line : paint) {
        inspect<vector<int>>(line);
    }

    return 0;
}

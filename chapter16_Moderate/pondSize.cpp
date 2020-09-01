#include <math.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
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
Pond Sizes: You have an integer matrix representing a plot of land,
where the value at that loca- tion represents the height above sea level.
A value of zero indicates water. A pond is a region of water connected
vertically, horizontally, or diagonally. The size of the pond is the total
number of connected water cells. Write a method to compute the sizes of all
ponds in the matrix.
*/

vector<int> pondSize(vector<vector<int>> land) {
    int landr = land.size();
    int landc = land[0].size();

    vector<int> result;

    // do bfs and mark every visited water -1
    // since all values are supposed to be >= 0 in the land matrix
    for (int r = 0; r < landr; ++r) {
        for (int c = 0; c < landc; ++c) {
            if (land[r][c] == 0) {
                queue<pair<int, int>> todo;
                todo.push({r, c});

                land[r][c] = -1;  // visit

                int pond_size = 1;

                while (not todo.empty()) {
                    pair<int, int> current = todo.front();
                    todo.pop();

                    vector<int> directions{1, -1, -1, 0, 1, 1, 0, -1, 1};

                    for (int d = 0; d < 8; ++d) {  // 8 directions
                        int cur_r = current.first + directions[d];
                        int cur_c = current.second + directions[d + 1];

                        if (cur_r >= 0 and cur_c >= 0 and cur_r < landr and
                            cur_c < landc and land[cur_r][cur_c] == 0) {
                            todo.push({cur_r, cur_c});
                            land[cur_r][cur_c] = -1;  // visit
                            pond_size++;
                        }
                    }
                }

                result.push_back(pond_size);
            }
        }
    }
    return result;
}

int main() {
    vector<vector<int>> land{
        {0, 2, 1, 0}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1}};

    auto result = pondSize(land);

    cout << "pond sizes are:\n";
    inspect<vector<int>>(result);

    return 0;
}

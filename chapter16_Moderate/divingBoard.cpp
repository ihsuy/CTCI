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
Diving Board: You are building a diving board by placing a bunch of
planks of wood end-to-end. There are two types of planks,
one of length shorter and one of length longer. You must use exactly K
planks of wood.Write a method to generate all possible lengths for the
diving board.
*/

void possibleBoardLength_helper(const int& k,
                                const int& b1,
                                const int& b2,
                                const int& len,
                                set<int>& result,
                                unordered_set<string>& alreadyGenerated) {
    if (k == 0) {
        result.insert(len);
        return;
    }

    string key = to_string(k) + " " + to_string(len);

    if (alreadyGenerated.count(key)) {
        return;
    }

    possibleBoardLength_helper(k - 1, b1, b2, len + b1, result,
                               alreadyGenerated);
    possibleBoardLength_helper(k - 1, b1, b2, len + b2, result,
                               alreadyGenerated);

    alreadyGenerated.insert(key);
}

set<int> possibleBoardLength_recursive(const int& k,
                                       const int& longer,
                                       const int& shorter) {  // extremely slow
    set<int> result;
    unordered_set<string> alreadyGenerated;
    possibleBoardLength_helper(k, longer, shorter, 0, result, alreadyGenerated);
    return result;
}

vector<int> possibleBoardLength(const int& k,
                                const int& longer,
                                const int& shorter) {
    if (longer == shorter) {
        return {longer * k};
    }

    vector<int> result;

    for (int i = 0; i <= k; ++i) {
        result.push_back(i * longer + (k - i) * shorter);
    }

    return result;
}

int main() {
    int l = 2;
    int s = 1;

    auto result = possibleBoardLength_recursive(25, l, s);
    inspect<set<int>>(result);

    auto result2 = possibleBoardLength(25, l, s);
    inspect<vector<int>>(result2);
    return 0;
}

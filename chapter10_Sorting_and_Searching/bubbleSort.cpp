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

#include "tools.cpp"

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
Bubble Sort : Runtime: O(n2) average and worst case. Memory: O(1).
In bubble sort, we start at the beginning of the array and swap the first
two elements if the first is greater than the second. Then, we go to the
next pair, and so on, continuously making sweeps of the array until it is
sorted. In doing so, the smaller items slowly "bubble" up to the beginning of
the list.
*/

void bubbleSort_naive(vector<int>& v) {
    int swapCount;
    do {
        swapCount = 0;
        for (int i = 0, j = 1; i < v.size() - 1;
             ++i, ++j) {  // since we are checking i and i+1 we need to stop at
                          // upperLimit-1
            if (v[i] > v[j]) {
                // bubbleSwap(v, i, j);
                swap(v[i], v[j]);
                swapCount++;
                // printf("Swap v[%d] and v[%d]: ", i, j);
                // inspect(v);
            }
        }
    } while (swapCount != 0);
}

void bubbleSort_optimal(vector<int>& v) {
    for (int c = 0; c < v.size(); ++c) {
        for (int i = 0, j = 1; i < v.size() - 1 - c; ++i, ++j) {
            if (v[i] > v[j]) {
                // bubbleSwap(v, i, j);
                swap(v[i], v[j]);
                // printf("Swap v[%d] and v[%d]: ", i, j);
                // inspect(v);
            }
        }
    }
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int N = 10000;
    // create N random integers and measure performance

    vector<int> v = gen(N);

    vector<int> v2 = v;

    timeIt(bubbleSort_naive, "bubbleSort_naive", v);
    timeIt(bubbleSort_optimal, "bubbleSort_optimal", v2);

    // inspect<vector<int>>(v);
    // cout << "---" << '\n';
    // inspect<vector<int>>(v2);

    return 0;
}

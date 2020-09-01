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
Contiguous Sequence: You are given an array of integers (both positive and
negative). Find the contiguous sequence with the largest sum. Return the sum.
*/

int contiguousSequence(const vector<int>& v) {
    int max_sum = INT_MIN;
    vector<int> runningSum(v.size(), 0);

    int prev = 0;

    while (v[prev] < 0) {
        if (v[prev] > max_sum) {
            max_sum = v[prev];
        }
        prev++;
    }

    runningSum[0] = v[prev];

    for (int i = prev + 1; i < v.size(); ++i) {
        runningSum[i] = runningSum[i - 1] + v[i];

        if (v[i] > max_sum) {
            max_sum = v[i];
        }

        if (runningSum[i] > runningSum[i - 1] and
            runningSum[i] > runningSum[prev]) {
            int temp = v[prev] - runningSum[prev] + runningSum[i];
            if (temp > max_sum) {
                max_sum = temp;
            }
        } else if (runningSum[i] > runningSum[i - 1]) {
            prev = i;
        }
    }
    return max_sum;
}

int contiguousSequence_simpler(const vector<int>& v) {
    int temp = 0;
    int max_sum = 0;

    for (int i = 0; i < v.size(); ++i) {
        temp += v[i];
        if (temp > max_sum) {
            max_sum = temp;
        } else if (temp < 0) {
            temp = 0;
        }
    }
    return max_sum;
}

int main() {
    vector<int> v{-8, 3, -2, 4, 1, -1, 5, -80, 6};
    vector<int> v2{2, 3, -8, -1, 2, 4, -2, 3};
    cout << "method1 largest sum: " << contiguousSequence(v) << '\n';
    cout << "method1 largest sum: " << contiguousSequence(v2) << '\n';

    cout << "method2 largest sum: " << contiguousSequence_simpler(v) << '\n';
    cout << "method2 largest sum: " << contiguousSequence_simpler(v2) << '\n';

    return 0;
}

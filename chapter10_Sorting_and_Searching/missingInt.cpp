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
Missing Int: Given an input file with four billion non-negative integers,
provide an algorithm to generate an integer that is not contained in the file.
Assume you have 1 GB of memory available for this task.
FOLLOW UP
What if you have only 10MB of memory? Assume that all the values are distinct
and we now have no more than one billion non-negative integers.
*/

int findMissingInt_1GB(
    const vector<unsigned long long>& v /*10m non-negative integers*/) {
    bitset<10000000> bs;

    for (auto& item : v) {
        bs.set(item);
    }

    for (unsigned long long i = 0; i < bs.size(); ++i) {
        if (bs[i] == 0) {
            return i;
        }
    }

    return -1;
}

int findMissingInt_10MB(
    const vector<unsigned long long>& v /*10m non-negative integers*/) {
    // divide into range 0~9999 10000~19999

    vector<int> rangeCount(v.size() / 10000);

    for (unsigned long long i = 0; i < v.size(); ++i) {
        unsigned long long low = 0, high = 9999;
        while (not(v[i] >= low and v[i] <= high)) {
            low = high + 1;
            high = low + 9999;
        }
        // found range
        rangeCount[low / 10000]++;
    }
    int rc = 0;
    for (; rc < rangeCount.size(); ++rc) {
        if (rangeCount[rc] < 10000) {  // missing int found here
            break;
        }
    }

    int low = 10000 * rc;
    int high = low + 9999;

    // use the bit vector method

    bitset<10000> bs;

    for (unsigned long long i = 0; i < v.size(); ++i) {
        if (v[i] >= low and v[i] <= high) {
            bs.set(v[i] - low);
        }
    }

    for (int i = 0; i < 10000; ++i) {
        if (bs[i] != 1) {
            return low + i;
        }
    }

    return -1;
}

int main() {
    vector<unsigned long long> v;
    int missingInt = 98765;
    for (unsigned long long i = 0; i < 1000000; ++i) {
        if (i == missingInt) {  // don't insert it
            continue;
        }
        v.push_back(i);
    }

    shuffle(v.begin(), v.end(),
            default_random_engine((int)chrono::high_resolution_clock::now()
                                      .time_since_epoch()
                                      .count()));
    // inspect<vector<int>>(v);

    cout << "missing: " << findMissingInt_1GB(v) << endl;
    cout << "missing: " << findMissingInt_10MB(v) << endl;

    return 0;
}

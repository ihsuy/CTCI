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
Find Duplicates: You have an array with all the numbers from 1to N,
where Nis at most 32,000.The array may have duplicate entries and you do not
know what N is. With only 4 kilobytes of memory available, how would you print
all duplicate elements in the array?
*/

void findDuplicates(const vector<int>& v) {
    bitset<32000> bs;

    for (int i = 0; i < v.size(); ++i) {
        if (bs[v[i]] == 0) {
            bs.set(v[i]);
        } else {
            cout << "duplicate found: " << v[i] << endl;
        }
    }
}

int main() {
    const int upperBound = 32000;

    auto v = gen(upperBound);

    // inspect<vector<int>>(v);

    findDuplicates(v);

    return 0;
}

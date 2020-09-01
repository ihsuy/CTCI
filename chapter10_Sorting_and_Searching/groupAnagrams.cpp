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
Group Anagrams:
Write a method to sort an array of strings
so that all the anagrams are next to each other.
*/

void groupAnagrams(vector<string>& v) {
    map<string, vector<string>> grouper;

    for (int i = 0; i < v.size(); ++i) {
        string word = v[i];
        sort(word.begin(), word.end());
        grouper[word].push_back(v[i]);
    }
    int k = 0;
    for (auto ite = grouper.begin(); ite != grouper.end(); ++ite) {
        for (int i = 0; i < ite->second.size(); ++i, ++k) {
            v[k] = ite->second[i];
        }
    }
}

int main() {
    vector<string> d{"yushi",       "anna",  "silent",      "ann",
                     "aann",        "ihsuy", "interesting", "entiristieng",
                     "interisteng", "listen"};

    groupAnagrams(d);

    inspect<vector<string>>(d);

    return 0;
}

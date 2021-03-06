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
Sparse Search: Given a sorted array of strings that is interspersed
with empty strings, write a method to find the location of a given string.
*/

int getLeftWord(const vector<string>& v, int i) {
    while (v[i] == "") {
        i--;
    }
    return i;
}

int getRightWord(const vector<string>& v, int i) {
    while (v[i] == "") {
        i++;
    }
    return i;
}

int sparseSearch(const vector<string>& v,
                 const int& low,
                 const int& high,
                 const string& word) {
    if (low > high) {
        return -1;
    }

    int mid = (low + high) / 2;

    int l = getLeftWord(v, mid);

    string leftWord = v[l];

    if (leftWord == word) {
        return l;
    } else if (leftWord > word) {
        return sparseSearch(v, low, l - 1, word);
    } else {
        int r = getRightWord(v, mid);

        string rightWord = v[r];

        if (rightWord == word) {
            return r;
        } else if (rightWord > word) {
            return -1;
        } else {
            return sparseSearch(v, r + 1, high, word);
        }
    }

    return -1;
}

int main() {
    vector<string> v{"at", "", "",    "", "", "",    "", "", "ball",
                     "",   "", "car", "", "", "dad", "", ""};

    cout << "Found at: " << sparseSearch(v, 0, v.size(), "ball") << '\n';

    return 0;
}

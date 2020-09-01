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
Pattern Matching:You are given two strings,
pattern and value.The pattern string consists of just the letter a and b,
describe a pattern within a string.
For example, the string catcatgocatgo matches the pattern aabab
(where cat is a and go is b). It also matches patterns like a, ab,
and b. Write a method to determine if value matches pattern .
*/

bool patternMatch(string s, string p) {
    size_t slen = s.length(), plen = p.length();

    // cout << "slen: " << slen << " plen: " << plen << '\n';

    if (slen == 0) {  // empty string doesn't match any pattern
        return false;
    }

    if (plen == 1) {  // single letter pattern matchs every string
        return true;
    }

    if (p[0] == 'b') {  // toggle a and b
        for (char& ch : p) {
            if (ch == 'b') {
                ch = 'a';
            } else {
                ch = 'b';
            }
        }
    }

    cout << "s: " << s << " p: " << p << '\n';

    size_t na = 0, nb = 0;
    // count number of as and number of bs
    for (char& ch : p) {
        if (ch == 'a') {
            na++;
        } else {
            nb++;
        }
    }

    // cout << "na: " << na << " nb: " << nb << '\n';

    if (nb == 0) {
        if (slen % na != 0) {
            return false;
        } else {
            size_t alen = slen / na;
            size_t pos = alen;
            string a = s.substr(0, alen);

            while (pos != slen) {
                string next = s.substr(pos, alen);
                if (next != a) {
                    return false;
                }
                pos += alen;
            }
            cout << "a: " << a << '\n';
            return true;
        }
    }

    size_t blen = 1, alen = slen - nb * blen;

    do {  // skip to the valid blen
        while (slen > nb * blen and (slen - nb * blen) % na != 0) {
            blen++;
        }

        if (slen > nb * blen) {
            alen = (slen - nb * blen) / na;
        } else {
            return false;
        }

        // cout << "alen: " << alen << " blen: " << blen << '\n';

        string a = s.substr(0, alen), b;

        size_t pos = alen;

        for (int i = 1; i < plen; ++i) {
            string next;
            if (p[i] == 'a') {
                next = s.substr(pos, alen);
                if (next != a) {
                    break;
                }
                pos += alen;
            } else {
                next = s.substr(pos, blen);
                if (b == "") {
                    b = next;
                } else if (next != b) {
                    break;
                }
                pos += blen;
            }
        }
        // cout << "pos: " << pos << '\n';
        if (pos == slen) {
            cout << "a: " << a << " b: " << b << endl;
            return true;
        }

        blen++;
    } while (alen > 1);

    return false;
}

int main() {
    string s = "catcatcatcatgocatgo";
    string p = "abb";

    cout << patternMatch(s, p) << '\n';

    return 0;
}

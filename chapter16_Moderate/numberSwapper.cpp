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
Number Swapper: Write a function to swap a number
in place (that is, without temporary vari- ables) .
*/

void numberSwapper(int& a, int& b) {  // straight forward elementary school math
    a = a + b;
    b = a - b;
    a = a - b;
}

void numberSwapper_bitmanip(int& a, int& b) {
    a = a ^ b;  // encode a and b in a
    b = a ^ b;  // retrieve a from a^b
    a = a ^ b;  // since b is now a, a^b will decode a and return b
}

int main() {
    int a = 123;
    int b = 321;

    cout << "before swap\na: " << a << " b: " << b << '\n';

    cout << "swapping a and b ...\n";
    numberSwapper(a, b);

    cout << "after arithmetic swap\na: " << a << " b: " << b << '\n';

    numberSwapper_bitmanip(a, b);
    cout << "swap again with bitmanip swap\na: " << a << " b: " << b << '\n';
    return 0;
}

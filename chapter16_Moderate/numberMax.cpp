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
Number Max: Write a method that finds the maximum of two numbers.
You should not use if-else or any other comparison operator.
*/

unsigned short signBit(int n) {  // this is for 32 bit integer
    return n >> 31 & 0x1;
}

int numberMax(int a, int b) {
    // Here, be careful when integer overflows
    // a = INT_MAX-2 and b = -3 will
    // make result of a-b overflow and turn it into a negative number
    // note this can only happen when one of a and b is negative
    // in this case the positive integer is absolutely larger
    // we immediently have the answer

    auto a_sign =
        signBit(a);  // 0 if positive 1 if negative (kinda confusing here)
    auto b_sign = signBit(b);
    auto diff_sign = signBit(a - b);  // sign of the different between a and b

    // want to know if a and b have the same sign
    unsigned short sign_diff = a_sign ^ b_sign;  // 1 if different
    // cout << "same sign: " << not sign_diff << '\n';

    // cout << "signs: " << a_sign << " " << b_sign << '\n';

    // if signs are the same we use the first half of the expression
    // 			(!diff_sign)*a + diff_sign*b
    // if signs are different, we use the second half of the expression
    // 			b_sign*a + a_sign*b
    return (!sign_diff) * ((!diff_sign) * a + diff_sign * b) +
           sign_diff * (b_sign * a + a_sign * b);
}

int main() {
    int a = INT_MAX - 2;
    int b = -101;
    cout << "a: " << a << "\nb: " << b << '\n';

    cout << "bigger number is: " << numberMax(a, b) << '\n';
    cout << "bigger number is: " << numberMax(b, a) << '\n';

    bitset<32> bs(1234);
    bitset<32> bs2(1234 ^ 1);
    cout << bs << endl;
    cout << (bs2) << endl;

    return 0;
}

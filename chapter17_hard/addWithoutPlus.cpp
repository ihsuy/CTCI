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
Add Without Plus: Write a function that adds two numbers.
You should not use + or any arithmetic operators.
*/

int bitmanip_add(const int& a, const int& b) {
    int mask = 1;
    int loc = 0;
    int result = 0;
    int carry = 0;

    int larger = ((a > b) ? a : b);
    while (mask <= larger) {  // get every bit
        int ba = ((a & mask) != 0);
        int bb = ((b & mask) != 0);

        // add bits and carry
        // note there are 2 cases for ba == bb
        // namely 0 0 and 1 1, both of them add up to 0
        // and there are 2 cases for ba != bb
        // namely 0 1 and 1 0, both of them add up to 1
        // this is equivalent to XOR
        // then we add carry using the same method
        int sum = (ba ^ bb) ^ carry;

        // carry is 0 if (ba + bb + previous_carry)>1
        // this is true when at least two of the 3 numbers are 1
        // we check if thats true or false
        carry = (ba & bb) | ((ba | bb) & carry);

        // add bit to result
        result |= (sum << loc);

        mask = mask << 1;

        loc++;
    }
    if (carry != 0) {  // deal with the case when last carry isn't 0
        result |= (carry << loc);
    }

    return result;
}

int bitmanip_add_smart(const int& a, const int& b) {
    if (b == 0) {  // no carry
        return a;
    }
    // only calculate sum
    int sum = a ^ b;
    // only calculate carry and shift left by 1
    // since carry is going to be added to the next digit
    int carry = (a & b) << 1;

    // recursively add carry to sum
    // until there's no carry
    return bitmanip_add_smart(sum, carry);
}

int main() {
    int a = 777;
    int b = 222;

    cout << bitmanip_add(a, b) << '\n';

    cout << bitset<16>(a) << '\n';
    cout << bitset<16>(b) << '\n';

    cout << bitmanip_add_smart(a, b) << '\n';

    return 0;
}

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
Coins: Given an innnite number of quarters (25 cents), dimes (10 cents),
nickels (5 cents), and pennies (1 cent),
write code to calculate the number of ways of representing n cents.
*/

int makeChange2_helper(const int& money,
                       const bool& useQ,
                       const bool& useD,
                       const bool& useN) {
    if (money < 0) {
        return 0;
    } else if (money < 5) {
        return 1;
    }

    int result = 0;

    if (useQ) {
        int q = money / 25;
        for (int i = 0; i <= q; ++i) {
            result += makeChange2_helper(money - i * 25, 0, 1, 1);
        }
    } else if (useD) {
        int d = money / 10;
        for (int i = 0; i <= d; ++i) {
            result += makeChange2_helper(money - i * 10, 0, 0, 1);
        }
    } else if (useN) {
        int n = money / 5;
        for (int i = 0; i <= n; ++i) {
            result += makeChange2_helper(money - i * 5, 0, 0, 0);
        }
    } else {
        result++;
    }

    return result;
}

int makeChange2(const int& money) {
    return makeChange2_helper(money, 1, 1, 1);
}

int makeChange_helper(const int& money,
                      const vector<int>& coins,
                      const int& index,
                      unordered_map<int, unordered_map<int, int>>& buffer) {
    if (index >= coins.size() - 1) {
        return 1;
    }

    int result = 0;

    for (int i = 0; i * coins[index] <= money; ++i) {
        int moneyLeft = money - i * coins[index];
        if (buffer.find(index) != buffer.end() and
            buffer[index].find(moneyLeft) != buffer[index].end()) {
            result += buffer[index][moneyLeft];
        } else {
            int temp = makeChange_helper(moneyLeft, coins, index + 1, buffer);
            buffer[index][moneyLeft] = temp;
            result += temp;
        }
    }
    return result;
}

int makeChange(const int& money) {
    vector<int> coins{25, 10, 5, 1};
    unordered_map<int, unordered_map<int, int>> buffer;
    return makeChange_helper(money, coins, 0, buffer);
}

int main() {
    int money = 10000;
    cout << makeChange(money) << '\n';
    cout << makeChange2(money) << '\n';

    return 0;
}

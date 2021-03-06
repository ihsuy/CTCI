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
Letters and Numbers: Given an array filled with letters and numbers,
find the longest subarray with an equal number of letters and numbers.
*/

// Solution 1 O(n^2)
// brute force solution
// compare lengths of all possible balanced (has same number of "numbers" and
// "letters") find the largest one
pair<int, int> findLongestBalancedSubarray(vector<char>& arr) {
    int result_low = 0, result_high = 0;

    for (int i = 0; i < arr.size(); ++i) {
        int temp_high = i;
        int num_count = 0, alpha_count = 0;
        for (int j = i; j < arr.size(); ++j) {
            if (isnumber(arr[j])) {
                num_count++;
            } else if (isalpha(arr[j])) {
                alpha_count++;
            }

            if (num_count == alpha_count) {
                temp_high = j;
            }
        }

        if (temp_high - i > result_high - result_low) {
            result_high = temp_high;
            result_low = i;
        }
    }

    return {result_low, result_high};
}

// solution 2 O(n)
// use 2 arrays b0 b1 to keep track of "how balanced the array is" (demonstrated
// below) input:   1a11a111a111aaaaaa balance: 101212343456543210 as shown
// above, we first prepare an integer "balance" whenever we see a number we
// increment balance else we decrement it by 1

// we discover that, if input[i] is an number, we need to find the most far j
// where balance[j] equal to balance[i]-1
// and if input[i] is a letter, we find balance[j] equal to balance[i]+1

pair<int, int> findLongestBalancedSubarray_faster(vector<char>& arr) {
    unordered_map<int, int> buffer;

    vector<pair<int, int>> b0, b1;

    unordered_set<int> seen0, seen1;

    int balance = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (isnumber(arr[i])) {
            balance++;
            if (seen1.count(balance) == 0) {
                seen1.insert(balance);
                b1.push_back({balance, i});
            }

        } else if (isalpha(arr[i])) {
            balance--;
            if (seen0.count(balance) == 0) {
                seen0.insert(balance);
                b0.push_back({balance, i});
            }
        }

        buffer[balance] = i;
    }

    int maxlen = 0, low = 0, high = 0;

    for (int i = 0; i < b1.size(); ++i) {
        int len = buffer[b1[i].first - 1] - b1[i].second + 1;
        if (len > maxlen) {
            maxlen = len;

            high = buffer[b1[i].first - 1];
            low = b1[i].second;
        }
    }

    for (int i = 0; i < b0.size(); ++i) {
        int len = buffer[b0[i].first + 1] - b0[i].second + 1;
        if (len > maxlen) {
            maxlen = len;
            high = buffer[b0[i].first + 1];
            low = b0[i].second;
        }
    }

    return {low, high};
}
int main() {
    vector<char> arr{'1', 'a', '1', '1', 'a', '1', '1', '1', 'a', '1',
                     '1', '1', 'a', 'a', 'a', 'a', 'a', '1', 'a'};
    auto result = findLongestBalancedSubarray(arr);
    auto longest = vector<char>{arr.begin() + result.first,
                                arr.begin() + result.second + 1};
    inspect<vector<char>>(longest);

    auto result2 = findLongestBalancedSubarray_faster(arr);
    auto longest2 = vector<char>{arr.begin() + result2.first,
                                 arr.begin() + result2.second + 1};
    inspect<vector<char>>(longest2);

    return 0;
}

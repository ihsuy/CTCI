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
Kth Multiple: Design an algorithm to find the kth number
such that the only prime factors are 3, 5, and 7.
Note that 3, 5, and 7 do not have to be factors,
but it should not have any other prime factors.
For example, the first several multiples
would be (in order) 1, 3, 5, 7, 9, 15, 21.
*/

// method 1 brute force
long long kthMultipleOf357_bf(const int& k) {
    vector<long long> v;
    v.reserve((k + 1) * (k + 1) * (k + 1));

    for (int a = 0; a <= k; ++a) {
        long long pa = pow(3, a);
        for (int b = 0; b <= k; ++b) {
            long long pb = pow(5, b);
            for (int c = 0; c <= k; ++c) {
                v.push_back(pa * pb * pow(7, c));
            }
        }
    }

    sort(v.begin(), v.end());

    return v[k - 1];
}
// method2
// find the smallest f*x thats larger than previous_result.back()
// where f is one of the factors {3,5,7} and x is one of the previous_results
long long kthMultipleOf357_O2(const int& k) {
    if (k < 0) {
        return 0;
    }

    vector<long long> factors{3, 5, 7};

    vector<long long> results{1};
    for (int i = 1; i <= k;
         ++i) {  // find the smallest product thats larger than results.back()
        long long minmax = LLONG_MAX;

        int f_high = 3;  // 3 different factors

        for (int j = 0; j < results.size(); ++j) {
            for (int f = 0; f < f_high; ++f) {
                long long temp_next = factors[f] * results[j];
                if (temp_next > results.back() and temp_next < minmax) {
                    minmax = temp_next;
                    // since the product is f*result[j]
                    // f and result are both in ascending order
                    // result[j+1] > result[j]
                    // thus f_new*result[j+1] > f_new*result[j]
                    // and we want f_new*result[j+1] to be smaller than
                    // f*result[j] we must have f_new < f
                    f_high = f;
                    break;
                }
            }

            if (f_high == 0) {  // at this point,
                // its impossible for f*results[j] to be any smaller
                break;
            }
        }
        results.push_back(minmax);
    }
    // inspect<vector<long long>>(results); // print the sequence
    return results[k];
}

// method 3
// try our best to avoid repeated work
// further exploit the property of the target sequence
int minOfThree(const long long& t1, const long long& t2, const long long& t3) {
    return min(t1, min(t2, t3));
}

long long kthMultipleOf357_optimal(const int& k) {
    if (k < 0) {
        return 0;
    }

    queue<long long> q3;
    queue<long long> q5;
    queue<long long> q7;
    q3.push(1);

    long long t = 0;

    for (int i = 0; i <= k;
         ++i) {  // setting value to llongmax when queues are empty
        // to forcely set t's value to the top of the non empty queue
        long long t3 = q3.empty() ? LLONG_MAX : q3.front();
        long long t5 = q5.empty() ? LLONG_MAX : q5.front();
        long long t7 = q7.empty() ? LLONG_MAX : q7.front();

        t = minOfThree(t3, t5, t7);
        // only push new values that hasn't already
        // appeared in any queues
        if (t == t3) {
            q3.pop();
            q3.push(3 * t);
            q5.push(5 * t);
        } else if (t == t5) {  // when t is t5, we know that the case
            // when t is t3 is already handled
            // because front of q3 will always have value
            // thats smaller than front of q5 and q7
            // and its first handled and removed
            q5.pop();
            q5.push(5 * t);
        } else if (t == t7) {
            q7.pop();
        }

        q7.push(7 * t);
    }

    return t;
}

int main() {
    // cout << kthMultipleOf357_bf(5) << '\n';
    cout << kthMultipleOf357_O2(100) << '\n';
    cout << kthMultipleOf357_optimal(100) << '\n';
    return 0;
}

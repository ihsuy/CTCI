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
Search in Rotated Array: Given a sorted array of n integers that
has been rotated an unknown number of times, write code to find an
element in the array. You may assume that the array was originally
sorted in increasing order.
*/

void rotateBy(vector<int>& v, const int& n) {
    reverse(v.begin(), v.end());
    reverse(v.begin(), v.begin() + n);
    reverse(v.begin() + n, v.end());
}

int find0(vector<int>& v) {  // use binary search to find the smallest
    // element in a rotated sorted array
    int low = 0, high = v.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (mid != v.size() - 1 and v[mid] > v[mid + 1]) {
            return mid + 1;
        } else if (v[mid] >= v[low]) {
            low = mid + 1;
        } else if (v[mid] < v[low]) {
            high = mid - 1;
        }
    }
    return 0;
}

int wrapIncrement(int i, const int& mod, const int& op) {
    if (i == op - 1) {
        return mod + 1;
    }
    return (i + 1) % mod;
}
int wrapDecrement(int i, const int& mod, const int& op) {
    if (i == op) {
        return -1;
    }

    i--;
    if (i < 0) {
        i += mod;
    }
    return i;
}

bool wrapLargerThan(const int& i, const int& j, const int& op, const int& mod) {
    if (i > mod or j < 0) {
        return true;
    }

    if (i < op and j < op) {
        return i > j;
    } else if (i < op and j >= op) {
        return true;
    } else if (i >= op and j < op) {
        return false;
    } else if (i >= op and j >= op) {
        return i > j;
    }
    throw runtime_error("unexpected input");
}

int wrapMid(int i, int j, const int& op, const int& mod) {
    int wp = mod - op;
    i = (i < op) ? (i + wp) : (i - op);
    j = (j < op) ? (j + wp) : (j - op);

    int true_mid = (i + j) / 2;
    if (true_mid < wp) {
        return true_mid + op;
    } else {
        return true_mid % wp;
    }
}

int searchRotatedArray_wrapping(
    vector<int>& v,
    const int n) {  // first find the true 0 position
    int op = find0(v);

    // do a wrapped binary search
    int wrapPosition = v.size();
    int low = op, high = (op == 0) ? wrapPosition - 1 : op - 1;

    while (not wrapLargerThan(low, high, op, wrapPosition)) {
        int mid = wrapMid(low, high, op, wrapPosition);

        if (v[mid] == n) {
            return mid;
        } else if (v[mid] > n) {
            high = wrapDecrement(mid, wrapPosition, op);
        } else {
            low = wrapIncrement(mid, wrapPosition, op);
        }
    }

    return -1;
}

int binarySearch(const vector<int>& v,
                 const int& low,
                 const int& high,
                 const int& val) {
    if (low > high) {
        return -1;
    }

    int mid = (high + low) / 2;

    if (v[mid] == val) {
        return mid;
    }

    if (v[mid] < val) {
        return binarySearch(v, mid + 1, high, val);
    } else {
        return binarySearch(v, low, mid - 1, val);
    }
}

int searchRotatedArray(vector<int>& v, const int n) {
    int op = find0(v);

    // check if n belongs to the left part of right part
    if (v[op] == n) {
        return op;
    }

    if (n <= v.back()) {  // n is in the right part
        // do binary search
        return binarySearch(v, op + 1, v.size() - 1, n);
    } else {  // on left
        return binarySearch(v, 0, op - 1, n);
    }
}

int main() {
    vector<int> v;
    for (int i = 1; i < 11; ++i) {
        v.push_back(i);
    }

    inspect<vector<int>>(v);

    rotateBy(v, 4);

    inspect<vector<int>>(v);

    cout << searchRotatedArray(v, 8) << endl;

    // cout << find0(v) << endl;

    // out << "mid" << wrapMid(0, 2, 2, 10) << '\n';

    return 0;
}

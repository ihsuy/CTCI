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
template <typename T>
inline void inspect(T& t, const std::string& sep = " ") {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << sep;
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Smallest K: Design an algorithm to find
the smallest K numbers in an array.
*/

void partition(vector<int>& arr, const int& lhs, const int& rhs, const int& K) {
    int l = lhs, r = rhs;
    auto pivot_i = rand() % (r - l + 1) + l;
    swap(arr[pivot_i], arr[l]);
    int pivot = arr[l];

    while (l < r) {
        if (arr[r] < pivot) {
            swap(arr[++l], arr[r]);
        } else {
            r--;
        }
    }
    swap(arr[l], arr[lhs]);

    if (l == K) {
        return;
    }

    if (l > K) {
        partition(arr, lhs, l - 1, K);
    } else {
        partition(arr, l + 1, rhs, K);
    }
}

vector<int> SmallestK(vector<int>& arr, const int& K) {
    int arrlen = arr.size();
    partition(arr, 0, arrlen - 1, K);
    inspect<vector<int>>(arr);
    return {arr.begin(), arr.begin() + K};
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    vector<int> nums{4, 2, 3, 0, 1, 8, 1, 4, 5, 0};
    auto res = SmallestK(nums, 3);
    inspect<vector<int>>(res, ", ");

    return 0;
}

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

int magicIndex_nodup_helper(const vector<int>& arr,
                            const int& begin,
                            const int& end) {
    if (begin > end) {
        return -1;
    }
    int mid = (begin + end) / 2;

    if (arr[mid] == mid) {  // found
        return mid;
    } else if (arr[mid] > mid) {
        return magicIndex_nodup_helper(arr, begin, mid - 1);
    } else {
        return magicIndex_nodup_helper(arr, mid + 1, end);
    }
}

int magicIndex_nodup(const vector<int>& arr) {
    return magicIndex_nodup_helper(arr, 0, arr.size() - 1);
}

int magicIndex_helper(const vector<int>& arr,
                      const int& begin,
                      const int& end) {
    if (begin > end) {
        return -1;
    }

    int mid = (begin + end) / 2;

    if (arr[mid] == mid) {
        return mid;
    } else if (arr[mid] < mid) {
        int left_result = magicIndex_helper(arr, begin, arr[mid]);
        if (left_result != -1) {
            return left_result;
        } else {
            return magicIndex_helper(arr, mid + 1, end);
        }
    } else {
        return magicIndex_helper(arr, begin, mid - 1);
    }
}

int magicIndex(const vector<int>& arr) {
    return magicIndex_helper(arr, 0, arr.size() - 1);
}

int main() {
    vector<int> arr;
    const int arr_size = 100000000;
    arr.reserve(arr_size);

    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = 0; i < arr_size; ++i) {
        arr.push_back(((rand() % 2 == 0) ? -1 : 1) * rand() % arr_size);
    }

    sort(arr.begin(), arr.end());
    // cout << magicIndex_nodup(arr) << endl;

    arr[arr_size - 1] = arr_size - 1;

    // arr = vector<int>{-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};

    int mi = magicIndex(arr);
    if (mi == -1) {
        cout << "No magic index found" << endl;
    } else {
        cout << "magic index: " << mi << endl;

        printf("arr[%i] = %i\n", mi, arr[mi]);
    }

    return 0;
}
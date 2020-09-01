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

using namespace std;

/*
Timing tool for measuring how long time the sort algorithm takes to sort an
array
*/

void timeIt(void (*sortAlgorithm)(vector<int>&),
            const string& name,
            vector<int>& v) {
    cout << "<<<<<<<<timeIt<<<<<<<<\n";
    int N = v.size();
    cout << "Sorting " << N << " integers...\n";

    auto t1 = chrono::high_resolution_clock::now();
    sortAlgorithm(v);
    auto t2 = chrono::high_resolution_clock::now() - t1;

    auto time_in_nano = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    auto time_in_micro =
        chrono::duration_cast<chrono::microseconds>(t2).count();

    cout << "Completed\n";
    cout << "Sorted " << N << " integers using " << name << '\n';
    cout << "Time elapsed:\n" << time_in_micro / 1000 << " milliseconds\n";
    cout << time_in_micro << " microseconds\n";
    cout << time_in_nano << " nanoseconds\n";
}

bool isSorted(vector<int>& v) {
    vector<int> cp = v;
    sort(cp.begin(), cp.end());
    return (cp == v);
}

bool isCorrectlySorted(const vector<int>& ov, const vector<int>& v) {
    vector<int> cp = ov;
    sort(cp.begin(), cp.end());

    return (cp == v);
}

vector<int> gen(const int& N) {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    cout << "Creating " << N << " integers...\n";

    vector<int> res;
    res.reserve(N);

    for (unsigned int i = 0; i < N; ++i) {
        res.push_back(rand() % N);
    }

    return res;
}

vector<unsigned long long> llgen(const unsigned long long& N) {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    cout << "Creating " << N << " unsigned long long integers...\n";

    vector<unsigned long long> res;
    res.reserve(N);

    for (unsigned long long i = 0; i < N; ++i) {
        res.push_back(rand() % N);
    }

    return res;
}
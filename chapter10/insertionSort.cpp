#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <list>
#include <chrono>
#include <random>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
#include <sstream>
#include <utility>
#include <bitset>
#include <string>
#include "timing.cpp"

typedef long long ll;
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Selection Sort IRuntime: O(n^2) average and worst case. Memory: 0(1) .
Selection sort is the child's algorithm: simple, but inefficient.
Find the smallest element using a linear scan and move it to the front
(swapping it with the front element).Then, find the second smallest and move it,
again doing a linear scan. Continue doing this until all the elements are in place.
*/

void insertionSort(vector<int>& v)
{
	for(int front = 0; front < v.size(); ++front)
	{
		for(int cur = front+1; cur < v.size(); ++cur)
		{
			
		}
	}
}

int main()
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	const int N = 100;
	// create N random integers and measure performance

	cout << "Creating " << N << " integers...\n";

	vector<int> v;
	v.reserve(N);

	for (int i = 0; i < N; ++i)
	{
		v.push_back(rand() % N);
	}

	insertionSort(v);

	inspect<vector<int>>(v);

	return 0;
}

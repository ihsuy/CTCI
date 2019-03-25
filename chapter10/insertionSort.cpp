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
#include "tools.cpp"

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

void insertionSort1(vector<int>& v)
{
	for(int front = 0; front < v.size(); ++front)
	{
		int min_i = front;
		for(int cur = front+1; cur < v.size(); ++cur)
		{
			if(v[cur] < v[min_i])
			{
				min_i = cur;
			}
		}
		swap(v[front], v[min_i]);
	}
}

void insertionSort2(vector<int>& v)
{	// maintain a sorted array in the head of v
	// constantly insert next element to the correct location in the sorted array
	for(int cur = 1; cur < v.size(); ++cur)
	{	// insert v[cur] to the sorted subarray before cur
		int sorted_i = cur-1;
		while(sorted_i >= 0 and v[sorted_i+1] < v[sorted_i])
		{	// swap v[cur] to the front and move every elements to their position + 1 
			// until an element smaller than v[cur] is found
			// put v[cur] after it
			swap(v[sorted_i], v[sorted_i+1]);
			sorted_i--;
		}
	}
}

int main()
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	const int N = 20000;
	// create N random integers and measure performance

	vector<int> v = gen(N);


	vector<int> v2 = v;

	timeIt(insertionSort1, "insertionSort1: insert the smallest from back" , v);

	timeIt(insertionSort2, "insertionSort2: insert next to correct position" , v2);

	return 0;
}

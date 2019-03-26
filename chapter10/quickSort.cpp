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
Quick Sort IRuntime: O(n log (n)) average, O(n2) worst case. Memory: O(log (n) ) .

In quick sort, we pick a random element and partition the array, such that all numbers
that are less than the partitioning element come before all elements that are greater than it.
The partitioning can be performed efficiently through a series of swaps (see below).
If we repeatedly partition the array (and its sub-arrays) around an element, the array will
eventually become sorted. However, as the partitioned element is not guaranteed to be the median
(or anywhere near the median), our sorting could be very slow.This is the reason for the 0 (n2)
worst case runtime.
*/

int partition_naive(vector<int>& v, const int& low, const int& high)
{
	// pick the right-most item as pivot
	//pivot = v[high];

	// left part should contain all the elements that are smaller than the pivot
	// right part vice versa
	int left = low, right = low;

	while (right < high)
	{
		if (v[right] < v[high])
		{
			swap(v[left], v[right]);
			left++;
		}
		right++;
	}
	// put pivot in its correct location
	swap(v[left], v[high]);

	return left;
}
void quickSort_naive_helper(vector<int>& v, const int& low, const int& high)
{
	if (low > high)
	{
		return;
	}

	int left = partition_naive(v, low, high);

	quickSort_naive_helper(v, low, left - 1);
	quickSort_naive_helper(v, left + 1, high);
}

void quickSort_naive(vector<int>& v)
{
	quickSort_naive_helper(v, 0, v.size() - 1);
}


// version 2

void insertionSort(vector<int>& v, const int& low, const int& high)
{
	for(int front = low; front <= high; ++front)
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

void insertionSort_wrapped(vector<int>& v)
{
	insertionSort(v, 0, v.size()-1);
}

int partition(vector<int>& v, const int& low, const int& high)
{
	// pick the middle item as pivot
	// this is better than picking corner items as pivot
	// because we don't have to swap that element to the middle at the end
	int pivot = v[(low + high) / 2];

	// left part should contain all the elements that are smaller than the pivot
	// right part vice versa
	int left = low, right = high;

	while (left <= right)
	{
		while (v[left] < pivot)
		{
			left++;
		}

		while (v[right] > pivot)
		{
			right--;
		}

		if (left <= right)
		{
			swap(v[left], v[right]);
			left++;
			right--;
		}
	}

	return left;
}

void quickSort_helper(vector<int>& v, const int& low, const int& high)
{
	// not sure why embedding insertion sort here slows down the algorithm significantly
	// since insertion sort is often faster when sorting an array with < 10 elements 
	// but it doesn't seem to work when combined with quick sort

	// if(high - low <= 9)
	// {
	// 	insertionSort(v, low, high);
	// 	return;
	// }
	int piv = partition(v, low, high);

	if (piv - 1 > low)
	{
		quickSort_helper(v, low, piv - 1);
	}
	if (piv < high)
	{
		quickSort_helper(v, piv, high);
	}
}

void quickSort(vector<int>& v)
{
	quickSort_helper(v, 0, v.size() - 1);
}

int main()
{
	int N = 1000000;
	vector<int> v = gen(N);
	vector<int> v2 = v;

	//inspect<vector<int>>(v);

	timeIt(quickSort, "quickSort", v);

	//timeIt(insertionSort_wrapped, "insertionSort", v2);

	//inspect<vector<int>>(v);

	cout << "is correctly sorted: " << isCorrectlySorted(v2, v) << '\n';


	return 0;
}



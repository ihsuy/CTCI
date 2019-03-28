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
Merge Sort | Runtime: O(n log (n)) average and worst case. Memory: Depends.

Merge sort divides the array in half, sorts each of those halves,
and then merges them back together. Each of those halves has the same sorting algorithm
applied to it. Eventually, you are merging just two single- element arrays.
It is the "merge" part that does all the heavy lifting.

The merge method operates by copying all the elements from the target array segment
into a helper array, keeping track of where the start of the left and right halves
should be (helperLeft and helperRight). We then iterate through helper,
copying the smaller element from each half into the array. At the end,
we copy any remaining elements into the target array.
*/

void merge(vector<int> & v, int low, int mid, int high, vector<int>& v_copy)
{	// note here, no new container is created
	// we simply copy the right elements into the same container v_copy
	copy(v.begin() + low, v.begin() + high + 1, v_copy.begin()+low);

	int k = low, left = low, right = mid + 1 ;
	while (left <= mid and right <= high)
	{
		if (v_copy[left] <= v_copy[right])
		{
			v[k] = v_copy[left];
			left++;
		}
		else
		{
			v[k] = v_copy[right];
			right++;
		}
		k++;
	}

	// do this only when left part isn't completely merged
	// because the right part is already in their correct location 
	int remain = mid - left;
	for (int i = 0; i <= remain; ++i)
	{
		v[k + i] = v_copy[left + i];
	}
}

void mergeSort_helper(vector<int>& v, const int& left, const int& right, vector<int>& v_copy)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;

	mergeSort_helper(v, left, mid, v_copy);
	mergeSort_helper(v, mid + 1, right, v_copy);

	merge(v, left, mid, right, v_copy);
}

void mergeSort(vector<int> & v)
{
	// v_copy will be used throughout the whole sorting process
	// as the reference to the original vector
	// no new vector should be created in this process
	// as allocating new vectors are VERY VERY unefficient 
	// (makes this algorithm 50 times slower)

	vector<int> v_copy(v.size());
	mergeSort_helper(v, 0, v.size() - 1, v_copy);
}

void cppSort(vector<int>& v)
{
	sort(v.begin(), v.end());
}

int main()
{
	const int N = 1000000;
	// create N random integers and measure performance

	vector<int> v = gen(N);
	vector<int> v2 = v;
	vector<int> v_copy = v;
	//inspect<vector<int>>(v);
	timeIt(mergeSort, "Merge Sort", v);
	//inspect<vector<int>>(v);
	cout << "correctly sorted: " << isCorrectlySorted(v_copy, v) << endl;

	timeIt(cppSort, "cpp algorithm sort", v);

	return 0;
}

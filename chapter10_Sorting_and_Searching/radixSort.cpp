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
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }
template<typename T>
inline void inspect(T& t){typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Radix Sort IRuntime: O( kn)
(see below)
Radix sort is a sorting algorithm for integers (and some other data types) 
that takes advantage of the fact that integers have a finite number of bits. 
In radix sort, we iterate through each digit of the number, grouping numbers by each digit. 
For example, if we have an array of integers, we might first sort by the first digit, 
so that the Os are grouped together. Then, we sort each of these groupings by the next digit. 
We repeat this process sorting by each subsequent digit. until finally the whole array is sorted.
Unlike comparison sorting algorithms, which cannot perform better than 0 (n log (n)) in the 
average case, radix sort has a runtime of O( kn), where n is the number of elements and k is 
the number of passes of the sorting algorithm.
*/


void radixSort_helper(vector<int>& v, const int& n /*nth digit to sort with respect to*/)
{	// create buckets 10
	// (there're only 10 different digits)
	vector<vector<int>> counter(10, vector<int>());


	for(int i = 0; i < v.size(); ++i)
	{
		// get the n-th digit of current value
		int mul = pow(10, n);
		int cur = (v[i]/mul)%10;

		// put it in its corresponding bucket
		counter[cur].push_back(v[i]);
	}

	// put everything back from the buckets
	int prevsz = 0;
	for(auto& item : counter)
	{
		copy(item.begin(), item.end(), v.begin()+prevsz);
		prevsz += item.size();
	}
}

void radixSort(vector<int>& v)
{
	// first find the largest value in v
	int mval = *max_element(v.begin(), v.end());

	// calculate number of digits in that value
	int nd = 0;
	do
	{
		nd++;
	}
	while(mval/=10);

	// number of digits obtained above will be the number
	// of function call to radixSort_helper
	for(int n = 0; n < nd; ++n)
	{	// since radixSort_helper does an inplace sorting on the array
		// continuously sort with respect to all digits (from the 0th to nd-th)
		// will result in a completely sorted array
		radixSort_helper(v, n);
	}
}

int main()
{
	int N = 10000000;
	vector<int> v = gen(N);
	vector<int> v2 = v;

	//inspect<vector<int>>(v);
	timeIt(radixSort, "radixSort", v);

	//inspect<vector<int>>(v);
	cout << "correct: " << isCorrectlySorted(v2, v) << '\n';
	return 0;
}

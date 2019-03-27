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
Peaks and Valleys: In an array of integers, a "peak" is an element which is
greater than or equal to the adjacent integers and a "valley" is an element
which is less than or equal to the adjacent inte- gers. For example, in the
array {5, 8, 6, 2, 3, 4, 6}, {8, 6} are peaks and {S, 2} are valleys. Given
an array of integers, sort the array into an alternating sequence of peaks
and valleys.
*/

void peakAndValleys_naive(vector<int>& v)
{
	// do a normal sort
	sort(v.begin(), v.end());

	// swap
	int len = v.size();
	if (len % 2 != 0)
	{
		len--;
	}
	for (int i = 0; i < len; i += 2)
	{
		swap(v[i], v[i+1]);
	}
}

void peakAndValleys_optimal(vector<int>& v)
{
	// there's no need to sort
	// Analysis:
	// let's say we have a sequence of number
	// and the first 2 numbers doesn form a peak_and_valley structure...
	// that's impossible! since two number has to be either a<b a>b and a==b
	// since all 3 possibilities forms the peak_and_valley structure, 
	// first 2 numbers are always going to be valid

	// Then, how about first 3 numbers? 

	// it's possible that its invalid, 
	// namely when they look something like:
	// n n+1 n+2 or n n-1 n-2
	// its simple to resolve: 
	// swap any 2 adjacent numbers

	// the rest of the problems can be solved by only considering
	// the last number in the past 3 numbers (already in peak_and_valley form) call it n
	// there're 2 possibilities: n is a valley or n is a peak
	// For case 1: 
	// its only problematic when the next number, let's call it m, is less than n
	// solution will be to simply swap n and m. Since m is less than n, m is qualified for
	// being the valley at n's position, and if we swap them, m is perfectly fine, 
	// and n is larger than m so becomes peak and its fine too
	// For case 2: 
	// exactly same approach can be applied. Since there's only trouble when next number m is 
	// larger than n, we can swap m and n, then m is the new peak and n becomes the valley
	// next to it.
	
	// By applying the same rules, by induction, we can transform the input array to 
	// a peak_and_valley sequence without sorting

	for(int i = 1; i < v.size()-1; ++i)
	{
		int h = v[i-1], n = v[i], m = v[i+1];
		if((h > n and m < n) or (h < n and m > n) or (h == n))
		{	// n is valley that's followed by m, m<n
			// or n is peak but followed by m, m>n
			// or when h and n are equal it could be either case, so swap m, n
			swap(v[i], v[i+1]);
		}
	}
}

int main()
{
	vector<int> v {200, 200, 1300, 180, 311, 3, 2,10,12, 0, 3, 4, 99, 190, 200};

	peakAndValleys_optimal(v);

	inspect<vector<int>>(v);

	return 0;
}

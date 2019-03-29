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
Smallest Difference: Given two arrays of integers,
compute the pair of values (one value in each array) with
the smallest (non-negative) difference.
Return the difference.
*/


pair<int, int> smallestDifference_helper(const vector<int>& v1, const vector<int>& v2)
{	// v1 and v2 are supposed to be sorted and for sake of optimization
	// size v2 is at least as small as size v1
	int min_diff = INT_MAX;
	pair<int, int> result;

	for(int i = 0; i < v1.size(); ++i)
	{	// binary search every element of v1 in v2

		int current = v1[i];

		int low = 0, high = v2.size()-1;

		while(low >= high)
		{
			int mid = (low + high)/2;

			if(v2[mid] == current)
			{	// found 0 difference, 
				// its ofc the answer
				return {current, current};
			}

			if(v2[mid] < current)
			{
				low = mid+1;
			}
			else
			{
				high = mid-1;
			}
		}
		// now the high and low should be
		// located at two cadidate values
		// compute the smaller difference
		int diff1 = abs(current - v2[low]);
		int diff2 = abs(current - v2[high]);
		if(diff1 < min_diff)
		{
			min_diff = diff1;
			result = {current, v2[low]};
		}
		if(diff2 < min_diff)
		{
			min_diff = diff2;
			result = {current, v2[high]};
		}
	}

	return result;
}

pair<int, int> smallestDifference(vector<int> v1, vector<int> v2)
{	// sort so we can do binary search
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	// for every value in v1 do binary search in v2
	// if its found, the difference is 0
	// and that's the smallest non-negative difference we can possibly have
	// if its not found, the answer must be one element before the stopping position
	// or one element after it (if exist)

	// a further optimization would be:
	// loop through the smaller vector and do binary search in the larger vector
	// since for M >> N, we have M*log(N) >> N*log(M)
	if(v1.size() > v2.size())
	{
		return smallestDifference_helper(v2, v1);
	}

	return smallestDifference_helper(v1, v2);
}

pair<int, int> smallestDifference_linearSearch(vector<int> v1, vector<int> v2)
{
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	int i1 = 0, i2 = 0;

	pair<int, int> result;

	int min_diff = INT_MAX;

	while(i1 < v1.size() and i2 < v2.size())
	{
		int diff = v1[i1] - v2[i2];

		int abs_diff = abs(diff);

		if(abs_diff < min_diff)
		{
			min_diff = abs_diff;
			result = {v1[i1], v2[i2]};
		}

		// if diff < 0, we want to make v1[i1] bigger -> i1++
		// else if diff > 0 we want to make v2[i2] bigger -> i2++
		// else 0 diff found answer
		if(diff == 0)
		{
			return {v1[i1], v2[i2]};
		}

		if(diff < 0)
		{
			i1++;
		}
		else
		{
			i2++;
		}
	}
	return result;
}

int main()
{
	vector<int> v1 {1, 3, 15, 11, 2};
	vector<int> v2 {23, 127, 235, 19, 8};

	auto result = smallestDifference(v1, v2);
	auto result2 = smallestDifference_linearSearch(v1, v2);
	cout << "pair of values with the smallest difference:\n";
	printf("method1: (%d, %d)\n", result.first, result.second);
	printf("method2: (%d, %d)\n", result2.first, result2.second);

	return 0;
}

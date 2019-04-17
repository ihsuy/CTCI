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
#include <fstream>
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
Majority Element: A majority element is an element
that makes up more than half of the items in an array.
Given a positive integers array, find the majority element.
If there is no majority element, return -1. Do this in
O(N) time and O(1) space.

EXAMPLE
Input: {1, 2, 5, 9, 5, 9, 5, 5, 5} Output: 5
*/

// brute force and ignore the restraint on space complexity
int majorityElement_bf(const vector<int>& nums)
{
	int half_sz = nums.size() / 2;
	// simply count the appearance of every number
	unordered_map<int, int> counter;
	for (auto& n : nums)
	{
		if (counter.count(n) == 0)
		{
			counter[n] = 1;
		}
		else
		{
			counter[n]++;
		}
	}
	// find the one that with appearance counter more than half size of nums
	for (auto i = counter.begin(); i != counter.end(); ++i)
	{
		if (i->second > half_sz)
		{
			return i->first;
		}
	}
	return -1;
}

// solution using O(1) space complexity (O(n) time complexity)
int majorityElement_optimal(const vector<int>& nums)
{	// go through nums twice
	// first time: find the most appearing element
	// second time: check if it appeared more than nums.size()/2 times
	int half_sz = nums.size() / 2;

	// find most frequently appearing number
	// use an counter to track the "dominance" of
	// quantity of any number. 
	// domiance: at least how much more times does the current best 
	// appears in the sequence
	int best = 0, dominance = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (dominance == 0)
		{	// 0 dominance would mean there's no single element in nums
			// has more appearance than all other elements
			best = nums[i];
			dominance++;
		}

		dominance += (nums[i] == best) ? 1 : -1;
	}

	// check if it did appear more than half_sz times
	int count = 0;
	for (const auto& n : nums)
	{
		if (n == best)
		{
			count++;
		}
	}

	return (count > half_sz) ? best : -1;
}

int main()
{
	vector<int> nums {1, 2, 5, 9, 5, 9, 5, 5, 5};
	cout << "brute force: " << majorityElement_bf(nums) << '\n';
	cout << "optimal:     " << majorityElement_optimal(nums) << '\n';

	return 0;
}

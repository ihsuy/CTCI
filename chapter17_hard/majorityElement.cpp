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

// brute force and ignore the restraint on time & space complexity
int majorityElement(const vector<int>& nums)
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

int main()
{
	vector<int> nums {1, 2, 5, 9, 5, 9, 5, 5, 5};
	cout << "brute force: " << majorityElement(nums) << '\n';

	return 0;
}

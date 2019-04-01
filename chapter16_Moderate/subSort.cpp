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
Sub Sort:
Given an array of integers, write a method to
find indices m and n such that if you sorted
elements m through n, the entire array would be sorted
minimize n-m
*/
bool isInCorrectLocation(const vector<int>& v, const int& idx)
{	// partition v using v[idx] as pivot
	// find how many elements are smaller than it
	int count = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] < v[idx])
		{
			count++;
		}
	}
	return (count == idx);
}

pair<int, int> subSort_naive(const vector<int>& v)
{
	int result_left = -1, result_right = -1;
	int low = 0, high = v.size() - 1;
	while (low < high)
	{
		if (result_left == -1 and (not isInCorrectLocation(v, low)))
		{
			result_left = low;
		}
		else if (result_left == -1)
		{
			low++;
		}
		if (result_right == -1 and (not isInCorrectLocation(v, high)))
		{
			result_right = high;
		}
		else if (result_right == -1)
		{
			high--;
		}

		if (result_left != -1 and result_right != -1)
		{
			return {result_left, result_right};
		}
	}

	return {0, 0}; // meaning, already sorted
}


pair<int, int> subSort_optimal(const vector<int>& v)
{
// assume v can be partitioned into 3 parts
// left sorted part, middle unsorted part, and right sorted part
// we find: the end of the left part and the begin of the right part
	int left_end = 0;
	for (int i = 1; i < v.size(); ++i)
	{
		if (v[i - 1] > v[i])
		{
			left_end = i - 1;
			break;
		}
	}
	if (left_end == v.size() - 1)
	{	// v is already sorted
		return {0, 0};
	}

	int right_begin = 0;
	for (int i = v.size() - 2; i >= 0; --i)
	{
		if (v[i + 1] < v[i])
		{
			right_begin = i + 1;
			break;
		}
	}

	// now we have partitioned v into 3 parts
	// next we find the largest value and the smallest value
	// in middle part
	int mid_max = v[left_end + 1];
	int mid_min = mid_max;
	for (int i = left_end + 2; i < right_begin; ++i)
	{
		if (v[i] > mid_max)
		{
			mid_max = v[i];
		}
		if (v[i] < mid_min)
		{
			mid_min = v[i];
		}
	}

	// next, find the last value in the left part of v
	// that is smaller than mid_min
	// and the first value in the right part of v
	// that is larger than mid_max
	// those are the results

	int result_left = 0, result_right = v.size()-1;

	for (int i = left_end; i >= 0; --i)
	{
		if (v[i] < mid_min)
		{
			result_left = i + 1;
			break;
		}
	}

	for (int i = right_begin; i < v.size(); ++i)
	{
		if (v[i] > mid_max)
		{
			result_right = i - 1;
			break;
		}
	}
	return {result_left, result_right};
}


int main()
{
	vector<int> v {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 17, 19};
	auto result1 = subSort_naive(v);
	cout << "subSort_naive: (" << result1.first << ", " << result1.second << ")" << endl;
	auto result2 = subSort_optimal(v);
	cout << "subSort_naive: (" << result2.first << ", " << result2.second << ")" << endl;
	return 0;
}

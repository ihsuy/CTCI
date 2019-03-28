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
Sorted Search, No Size: You are given an array-like data structure Listy which
lacks a size method.It does, however, have an elementAt(i) method that returns 
the element at index i in 0(1) time. If i is beyond the bounds of the data structure, 
it returns -1. (For this reason, the data structure only supports positive integers.) 
Given a Listy which contains sorted, positive integers, find the index at which an 
element x occurs. If x occurs multiple times, you may return any index.
*/

int elementAt(const vector<int>& v, const int& n)
{
	if(n >= v.size() or n < 0)
	{
		return -1;
	}

	return v[n];
}

int sortedSearchNoSize(const vector<int>& v, const int& n)
{	// v.size() is banned, only elementAt is available
	int i = 1;
	int val = elementAt(v, i);

	while(val < n and val != -1)
	{
		i *= 2;
		val = elementAt(v, i);
	}

	int low = 0, high = i;

	while(low <= high)
	{
		int mid = (low + high)/2;

		if(elementAt(v, mid) == n)
		{
			return mid;
		}

		if(elementAt(v, mid) == -1 or elementAt(v, mid) > n)
		{
			high = mid-1;
		}
		else if(elementAt(v, mid) < n)
		{
			low = mid+1;
		}
	}

	return -1;
}

int main()
{
	vector<int> v;
	for (int i = 1; i < 1000; ++i)
	{
		v.push_back(i);
	}

	//inspect<vector<int>>(v);

	cout << sortedSearchNoSize(v, 99) << endl;

	return 0;
}

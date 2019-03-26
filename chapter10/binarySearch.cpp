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
In binary search, we look for an element x in a sorted array by first
comparing x to the midpoint of the array. If x is less than the midpoint,
then we search the left half of the array. If x is greater than the midpoint,
then we search the right half of the array. We then repeat this process,
treating the left and right halves as subar- rays. Again, we compare x to the
midpoint of this subarray and then search either its left or right side.
We repeat this process until we either find x or the subarray has size O.
*/

int binarySearch_helper(const vector<int>& v, const int& val, const int& low, const int& high)
{
	if (low > high)
	{
		return -1;
	}

	int mid = (low + high) / 2;
	int vmid = v[mid];

	if (vmid == val)
	{
		return mid;
	}

	if (vmid > val)
	{
		return binarySearch_helper(v, val, low, mid - 1);
	}
	else
	{
		return binarySearch_helper(v, val, mid + 1, high);
	}

}

int binarySearch_recursive(const vector<int>& v, const int& val)
{
	return binarySearch_helper(v, val, 0, v.size() - 1);
}

int binarySearch_iterative(const vector<int>& v, const int& val)
{
	int low = 0, high = v.size();

	while(low <= high)
	{
		int mid = (low+high)/2;
		int midval = v[mid];
		if(midval > val)
		{	// search left
			high = mid-1;
		}
		else if(midval < val)
		{	// search right
			low = mid+1;
		}
		else
		{	// found
			return mid;
		}
	}

	return -1;
}

int main()
{
	vector<int> v{21,5,1,2,5,12,0,4,5,6,1,2,3,1,2};

	sort(v.begin(), v.end());

	inspect<vector<int>>(v);

	cout << binarySearch_iterative(v, 21) << '\n';

	cout << binarySearch_recursive(v, 21) << '\n';

	return 0;
}

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
Sum Swap: Given two arrays of integers,
find a pair of values (one value from each array)
that you can swap to give the two arrays the same sum.

Input: (4, 1, 2, 1, 1, 2) and (3, 6, 3, 3)
Output: (1, 3)
*/

pair<int, int> sumSwap(const vector<int>& v1, const vector<int>& v2)
{	// note that swaping will ONLY cause 2 vectors to increase and decrease by
	// same amount, i.e. of swapping causes sum(v1) to decrease by A then sum(v2) will
	// be increased by A.
	// Assume sum(v1) = s1 and sum(v2) = s2,
	// now we want their sum to be the same by swapping
	// that is, we're looking for integer A such that s1 + A == s2 - A
	// this can be refactored to A == (s2-s1)/2
	// now we only need to find a pair of elements {e1, e2} from v1 and v2
	// such that e2-e1 == A

	int sum1 = accumulate(v1.begin(), v1.end(), 0), sum2 = accumulate(v2.begin(), v2.end(), 0);

	unordered_set<int> v2_set(v2.begin(), v2.end());

	int target = (sum2 - sum1);

	if (target % 2 != 0)
	{
		cout << "Can't swap to make sum(v1) == sum(v2)\n";
		return {0, 0};
	}

	target /= 2;

	for (int i = 0; i < v1.size(); ++i)
	{
		int wanted = target + v1[i];

		if (v2_set.count(wanted) != 0)
		{
			return {v1[i], wanted};
		}
	}

	return {0, 0};

}

int main()
{
	const vector<int> v1 {4, 1, 2, 1, 1, 2};
	const vector<int> v2 {3, 6, 3, 3};

	pair<int, int> result = sumSwap(v1, v2);

	cout << "(" << result.first << ", " << result.second << ")\n";

	return 0;
}

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
Random Set: Write a method to randomly generate a set of m integers
from an array of size n.
Each element must have equal probability of being chosen.
*/

vector<int> randomSet(vector<int> baseSet, int m)
{	// this is very similar to problem "shuffle" in the same chapter
	if (m > baseSet.size())
	{
		m = baseSet.size();
	}

	for (int i = 0; i < m; ++i)
	{
		size_t idx = rand() % (baseSet.size() - i);
		swap(baseSet[idx], baseSet[i]);
	}

	return vector<int> {baseSet.begin(), baseSet.begin() + m};
}

int main()
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	vector<int> baseSet {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	auto result =randomSet(baseSet, 5);
	inspect<vector<int>>(result);


	return 0;
}

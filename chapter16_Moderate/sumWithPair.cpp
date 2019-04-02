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
Pairs with Sum: Design an algorithm to find all
pairs of integers within an array which sum to a specified value.
*/

vector<pair<int, int>> pairWithSum(const vector<int>& v, const int& target)
{
	vector<pair<int, int>> result;

	unordered_map<int, int> unique_elementCounter;
	for (int i = 0; i < v.size(); ++i)
	{
		if (unique_elementCounter.count(v[i]) == 0)
		{
			unique_elementCounter[v[i]] = 1;
		}
		else
		{
			unique_elementCounter[v[i]]++;
		}
	}

	for (int i = 0; i < v.size(); ++i)
	{
		int val2 = target - v[i];
		bool sameVal = (val2 == v[i]);

		if (unique_elementCounter.count(v[i]) != 0
		        and unique_elementCounter.count(val2) != 0
		        and not (sameVal and unique_elementCounter[v[i]] < 2))
		{
			result.push_back({v[i], val2});

			unique_elementCounter.erase(v[i]);
			if (not sameVal)
			{
				unique_elementCounter.erase(val2);
			}
		}
	}

	return result;
}


int main()
{
	vector<int> v = {6, 1, 1, 0, 3, 3, 6, 5, 7, 2, 2};
	auto result = pairWithSum(v, 6);
	for(auto& item : result)
	{
		cout << "(" << item.first << ", " << item.second << ")\n";
	}

	return 0;
}

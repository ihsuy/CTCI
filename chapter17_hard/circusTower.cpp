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
Circus Tower: A circus is designing a tower
routine consisting of people standing atop
one another's shoulders. For practical and
aesthetic reasons, each person must be both
shorter and lighter than the person below him or
her. Given the heights and weights of each person in
the circus, write a method to compute the largest possible
number of people in such a tower.
Input (ht, wt): (65, 100), (70, 150), (56, 90), (75, 190), (60, 95), (68, 110)
Output: The longest tower is length 6 and includes from top to bottom:
(56, 90), (60, 95), (65, 100), (68, l10), (70, 150), (75, 190)
*/


// brute force
int highestTower_bf_helper(vector<pair<int, int>> people, const int& prev, 
	unordered_map<int, int>& buffer)
{
	int maxh = 0;
	for (int i = 0; i < people.size(); ++i)
	{
		if (people[i].first > people[prev].first
		        and people[i].second > people[prev].second)
		{	// valid person to be under "people[prev]" has to be
			// both taller and heavier
			int lower_result = 0;
			if(buffer.count(i) != 0)
			{
				lower_result = buffer[i];
			}
			else
			{
				lower_result = highestTower_bf_helper(people, i, buffer);
				buffer[i] = lower_result;
			}
			int temp = lower_result + people[i].first;
			if (temp > maxh)
			{
				maxh = temp;
			}
		}
	}
	return maxh;
}

int highestTower_bf(const vector<pair<int, int>>& people)
{
	int maxh = 0;
	unordered_map<int, int> buffer;
	for (int top = 0; top < people.size(); ++top)
	{
		auto h = highestTower_bf_helper(people, top, buffer) + people[top].first;
		if (h > maxh)
		{
			maxh = h;
		}
	}
	return maxh;
}

int main()
{
	vector<pair<int, int>> ppl {{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
	cout << highestTower_bf(ppl) << '\n';

	return 0;
}

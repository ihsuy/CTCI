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
Sorted Merge: You are given two sorted arrays, A and B,
where A has a large enough buffer at the end to hold B.
Write a method to merge B into A in sorted order.
*/

void sortedMerge1(vector<int>& a, vector<int>& b)
{	// use an extra array
	vector<int> e(a.size());

	int i = 0, j = 0, k = 0;
	while (i < a.size() and j < b.size())
	{
		int cur_a = a[i], cur_b = b[j];
		if (cur_a < cur_b)
		{
			e[k] = cur_a;
			i++;
		}
		else if (cur_b <= cur_a)
		{
			e[k] = cur_b;
			j++;
		}
		k++;
	}
	if (i == a.size())
	{
		for (; j < b.size(); ++j, ++k)
		{
			e[k] = b[j];
		}
	}
	else
	{
		for (; i < a.size(); ++i, ++k)
		{
			e[k] = a[i];
		}
	}
	a = e;
}

void sortedMerge2(vector<int>& a, const int& a_size, vector<int>& b)
{	// in place
	// trick is to insert to the back of a
	int k = a.size() - 1;
	int i = a_size - 1, j = b.size() - 1;

	while (j >= 0)
	{	// terminate only when we finish iterating b
		if (i >= 0 and a[i] > b[j])
		{	// won't enter here if i is exhausted first
			a[k] = a[i];
			i--;
		}
		else
		{
			a[k] = b[j];
			j--;
		}
		k--;
	}
}

int main()
{
	int N = 10;
	int a_size = N/3;
	int b_size = N - a_size;

	vector<int> a(N);
	vector<int> b(b_size);

	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	for (int i = 0; i < a_size; ++i)
	{
		a[i] = rand() % N;
	}

	for (int i = 0; i < b_size; ++i)
	{
		b[i] = rand() % N;
	}

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	// rotate
	reverse(a.begin(), a.end());
	reverse(a.begin(), a.begin() + a_size);

	cout << "A: ";
	inspect<vector<int>>(a);
	cout << "B: ";
	inspect<vector<int>>(b);
	cout << "Merging B to A...\n";
	sortedMerge2(a, a_size, b);
	cout << "A: ";
	inspect<vector<int>>(a);


	return 0;
}

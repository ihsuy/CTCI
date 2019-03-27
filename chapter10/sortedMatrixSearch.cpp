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
Sorted Matrix Search: Given an M x N matrix in which each row
and each column is sorted in ascending order, write a method
to find an element.
*/

pair<int, int> sortedMatrixSearch_dumb(const vector<vector<int>>& m, const int& val)
{
	int width = m[0].size(), height = m.size();

	vector<bool> isValidCol(width, true);
	vector<bool> isValidRow(height, true);

	// look at margin to elimiated invalid rows and colums
	for (int i = 0; i < width; ++i)
	{
		if (not (val >= m[0][i] and val <= m[height - 1][i]))
		{
			isValidCol[i] = false;
		}

		if (val == m[0][i])
		{
			return {0, i};
		}

		if (val == m[height - 1][i])
		{
			return {height - 1, i};
		}
	}

	for (int i = 0; i < height; ++i)
	{
		if (not (val >= m[i][0] and val <= m[i][width - 1]))
		{
			isValidRow[i] = false;
		}

		if (val == m[i][0])
		{
			return {i, 0};
		}

		if (val == m[i][width - 1])
		{
			return {i, width - 1};
		}
	}

	for (int i = 1; i < height - 1; ++i)
	{
		if (isValidRow[i])
		{
			for (int j = 1; j < width - 1; ++j)
			{
				if (isValidCol[j])
				{
					if (m[i][j] == val)
					{
						return {i, j};
					}

					if (m[i][j] > val)
					{
						int r = i, c = j;

						while (r < height - 1)
						{
							isValidRow[r] = false;
							r++;
						}

						while (c < width - 1)
						{
							isValidCol[c] = false;
							c++;
						}
					}
				}
			}
		}
	}
	return { -1, -1};
}

pair<int, int> sortedMatrixSearch_optimal(const vector<vector<int>>& m, const int& val)
{
	int width = m[0].size(), height = m.size();
	// starting point
	int r = 0;
	int c = width - 1;

	while (r < height and c < width)
	{
		int cur = m[r][c];

		if (cur == val)
		{
			return {r, c};
		}

		if (cur > val)
		{
			c--;
		}
		else if (cur < val)
		{
			r++;
		}
	}

	return { -1, -1};
}

pair<int, int> sortedMatrixBinarySearch(const vector<vector<int>>& m,
                                        const int& rowl, const int& rowr,
                                        const int& coll, const int& colr,
                                        const int& val)
{
	cout << "rowl: " << rowl << " rowr: " << rowr << " coll: " << coll << " colr: " << colr << '\n';
	int rl = rowl, rr = rowr, cl = coll, cr = colr;

	if (rl > rr or cl > cr)
	{
		return { -1, -1};
	}
	int prev_r = rl, prev_c = cl;
	while (rl <= rr and cl <= cr)
	{
		if (m[rl][cl] == val)
		{
			return {rl, cl};
		}

		if (m[rl][cl] > val)
		{
			cout << "found diag: " << rl << " " << cl << endl;
			auto result = sortedMatrixBinarySearch(m, rl, rr, coll, prev_c, val);
			if(result != pair<int, int>(-1, -1))
			{
				return result;
			}
			return sortedMatrixBinarySearch(m, rowl, prev_r, cl, colr, val);
		}

		// iterative alone diagonal
		prev_r = rl;
		prev_c = cl;
		rl++;	
		cl++;
	}

	if(rl > rr and cl <= cr and val > m[prev_r][prev_c])
	{
		return sortedMatrixBinarySearch(m, rowl, prev_r, prev_c+1, cr, val);
	}
	else if(cl > cr and rl <= rr and val > m[prev_r][prev_c])
	{
		return sortedMatrixBinarySearch(m, prev_r+1, rr, coll, prev_c, val);
	}

	return {-1, -1};
}

int main()
{
	vector<vector<int>> m
	{
		{1, 3, 4, 6, 7},
		{4, 5, 5, 7, 9},
		{5, 5, 6, 7, 10},
		{6, 8, 9, 9, 10},
		{7, 9, 10, 10, 11},
		{8, 11, 19, 20, 21}
	};

	auto result = sortedMatrixSearch_optimal(m, 8);

	cout << "optimal r: " << result.first << " c: " << result.second << '\n';

	result = sortedMatrixBinarySearch(m, 0, m.size()-1, 0, m[0].size()-1, 19);

	cout << "r: " << result.first << " c: " << result.second << '\n';

	return 0;
}

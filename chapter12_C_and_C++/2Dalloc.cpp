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
20 Alloc: Write a function in
( called my2DAlloe which allocates a two-dimensional array.
Minimize the number of calls to malloc and make sure that the memory is
accessible by the notation arr[i][j].
*/

int** array2D_sepBlocks(const int& r, const int& c)
{	// allocate different memory blocks for each row
	// first allocate an array of pointers of pointers
	int** rows = (int**)malloc(sizeof(int**)*r);
	for (int i = 0; i < r; ++i)
	{
		rows[i] = new int[c];
		memset(rows[i], 0, sizeof(int)*c);
	}

	return rows;
}

int** array2D_oneBlock(const int& r, const int& c)
{	// allocate the hole 2d array in one memory block

	// allocate 1 extra row for storing pointers to every row
	int** rows = (int**)malloc(sizeof(int*) * (r * c + 1));

	for (int i = 0; i < r; ++i)
	{
		rows[i] = (int*)&rows[r * (i + 1)];
	}

	// fill in initial values
	for (int i = r; i < (r + 1)*c; ++i)
	{
		rows[i] = 0;
	}

	return rows;
}

int main()
{
	int** maxtrix = array2D_sepBlocks(5, 5);
	cout << "matrix1: rows allocated on seperate memory blocks\n";
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << maxtrix[i][j] << ' ';
		}
		cout << '\n';
	}

	int** maxtrix2 = array2D_oneBlock(5, 5);
	cout << "matrix2: everything allocated on the same memory block\n";
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << maxtrix2[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}

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
Bisect Squares: Given two squares on a two-dimensional plane,
find a line that would cut these two squares in half.
Assume that the top and the bottom sides of the square run parallel to the x-axis.
*/

struct square
{
	double width;
	pair<int, int> center;
	square(const double& w, const pair<int, int>& c) : width(w), center(c) {}

	// other implementations could be
	// methods for finding coordinates for the 4 corners or area, etc.
};

string bisectSquares(const square& sq1, const square& sq2)
{	// to find a line that cuts two different sqaure into half
	// is to find a line that goes through both squares' center
	// since every line that goes through the center of a square
	// will cut the square into 2 symmetrical halfs

	// calculate slope and intercept for the line
	double c1x = sq1.center.first;
	double c1y = sq1.center.second;

	double c2x = sq2.center.first;
	double c2y = sq2.center.second;

	// deal with the case when two squares
	// align to the center perpendicularly
	if (c1x == c2x)
	{
		return "x = " + to_string(c1x);
	}

	double k = (c1y - c2y) / (c1x - c2x);

	double b = c1y - c1x * k;

	string result = "y = ";

	if (k != 0)
	{
		result += to_string(k) + "x";
		if (b != 0)
		{
			result += (b > 0) ? (" + " + to_string(b)) : (" - " + to_string(-b));
		}
	}
	else if (b != 0)
	{
		result += to_string(b);
	}

	else if (k == 0)
	{
		result += "0";
	}

	return result;
}

int main()
{
	square s1(5, { -4, 4});
	square s2(7, {10, 15});

	cout << "bisect line: " << bisectSquares(s1, s2) << endl;

	square s3(7, {4, 4}); // align horizontally

	cout << "bisect line: " << bisectSquares(s1, s3) << endl;

	square s4(6, {10, 30}); // align vertically

	cout << "bisect line: " << bisectSquares(s2, s4) << endl;
	return 0;
}

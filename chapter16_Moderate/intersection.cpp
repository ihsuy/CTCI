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
Intersection: Given two straight line segments
(represented as a start point and an end point),
compute the point of intersection, if any.
*/

pair<double, double> line_intersection(const pair<double, double>& p11, const pair<double, double>& p12,
                                       const pair<double, double>& p21, const pair<double, double>& p22)
{
	if((p11.first - p12.first) == 0 or (p21.first - p22.first) == 0)
	{
		throw runtime_error ("can't handle vertical lines");
	}
	// calculate slopes k1, k2 for two lines
	double k1 = (p11.second - p12.second) / (p11.first - p12.first);
	double k2 = (p21.second - p22.second) / (p21.first - p22.first);

	cout << "slopes:  k1: " << k1 << " k2: " << k2 << '\n';

	// calculate intercept b1 and b2

	double b1 = p11.second - p11.first * k1;
	double b2 = p21.second - p21.first * k2;

	cout << "intercepts:  b1: " << b1 << " b2: " << b2 << '\n';

	if (k1 == k2)
	{	// parallel -> no intersection unless they are the same line
		if (b1 == b2)
		{	// same line
			throw runtime_error("same lines intersects everywhere");
		}
		throw runtime_error("parallel lines intersects nowhere");
	}

	// calculate intersections
	double x = (b2 - b1) / (k1 - k2);
	double y = x * k1 + b1;

	return {x, y};
}

pair<double, double> lineSegments_intersection(
    const pair<double, double>& p11, const pair<double, double>& p12,
    const pair<double, double>& p21, const pair<double, double>& p22
)
{
	pair<double, double> p = line_intersection(p11, p12, p21, p22);

	double x = p.first;
	double y = p.second;

	cout << x << " " << y << '\n';

	// check if p is on both line1 and line2

	double line1_x_high = (p11.first > p12.first) ? p11.first : p12.first;
	double line1_x_low = (p11.first < p12.first) ? p11.first : p12.first;

	double line1_y_high = (p11.second > p12.second) ? p11.second : p12.second;
	double line1_y_low = (p11.second < p12.second) ? p11.second : p12.second;

	double line2_x_high = (p21.first > p22.first) ? p21.first : p22.first;
	double line2_x_low = (p21.first < p22.first) ? p21.first : p22.first;

	double line2_y_high = (p21.second > p22.second) ? p21.second : p22.second;
	double line2_y_low = (p21.second < p22.second) ? p21.second : p22.second;


	if (x >= line1_x_low and x <= line1_x_high and
	        x >= line2_x_low and x <= line2_x_high and
	        y >= line1_y_low and y <= line1_y_high and
	        y >= line2_y_low and y <= line2_y_high)
	{
		return {x, y};
	}

	throw runtime_error("no intersection");
}

int main()
try{
	pair<double, double> p11{4, 2}, p12{4, 4}, p21{1, 1}, p22{2, 2};

	pair<double, double> intersection = lineSegments_intersection(p11, p12, p21, p22);

	cout << "intersection at: (" << intersection.first << ", " << intersection.second << ")\n";

	return 0;
}
catch(runtime_error& re)
{
	cout << "error: " << re.what() << '\n';
}

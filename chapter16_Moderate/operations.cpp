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
Operations: Write methods to implement the multiply, subtract, and divide
operations for integers. The results of all of these are integers.
Use only the add operator.
*/

int flip_sign_(const int& a)
{
	return (~a) + 1;
}

int flip_sign(int a)
{	// use + only
	if(a == 0)
	{
		return 0;
	}

	int tmp_inc = a < 0 ? -1 : 1;
	int res_inc = a < 0 ? 1 : -1;

	int result = 0;
	int temp = 0;

	if (a < 0)
	{
		while (temp > a)
		{
			temp += tmp_inc;
			result += res_inc;

			tmp_inc += tmp_inc;
			res_inc += res_inc;
		}
	}
	else
	{
		while (temp < a)
		{
			temp += tmp_inc;
			result += res_inc;

			tmp_inc += tmp_inc;
			res_inc += res_inc;
		}
	}

	tmp_inc = a < 0 ? -1 : 1;
	res_inc = a < 0 ? 1 : -1;

	while (temp != a)
	{
		temp += res_inc;
		result += tmp_inc;
	}

	return result;
}

int p_subtract(const int& a, const int& b)
{
	return a + flip_sign(b);
}

bool validate_input(int& a, int& b)
{
	bool neg = false;

	if ((a > 0 and b < 0) or (a < 0 and b > 0))
	{
		if (a < 0)
		{
			a = flip_sign(a);
		}
		else if (b < 0)
		{
			b = flip_sign(b);
		}
		neg = true;
	}
	else if (a < 0 and b < 0)
	{
		a = flip_sign(a);
		b = flip_sign(b);
	}

	return neg;
}

int p_multiply(int a, int b)
{
	bool neg = validate_input(a, b);

	int result = 0;
	for (int i = 0; i < b; ++i)
	{
		result += a;
	}

	return (neg) ? flip_sign(result) : result;
}

int p_mod(int a, int b)
{	// this only handles positive numbers a, b
	// and used bit manip operations
	if (a < b)
	{
		return a;
	}
	if (a == b)
	{
		return 0;
	}

	// now a must be larger than b

	while (a > (b << 2))
	{
		b <<= 2;
	}

	return p_subtract(a, b);
}

int p_divide(int a, int b)
{
	bool neg = validate_input(a, b);

	if ((a == 0 or a < b) and b != 0)
	{
		return 0;
	}
	else if (b == 0)
	{
		throw runtime_error("division by zero");
	}

	if (a == b)
	{
		return 1;
	}

	// now b isn't zero, a doesn't not equal b
	// and a larger than b
	// following is the the nontrivial case
	int mul = 0;
	int temp = 0;

	do
	{
		mul++;
		temp = p_multiply(b, mul);
	}
	while (a > temp);

	if (a != temp)
	{
		mul--;
	}

	return (neg) ? flip_sign(mul) : mul;
}

int main()
{
	int a = 24;
	int b = 8;

	cout << p_subtract(a, b) << '\n';
	cout << p_subtract(b, a) << '\n';
	cout << p_multiply(a, b) << '\n';
	cout << p_multiply(b, a) << '\n';

	cout << p_divide(a, b) << endl;

	cout << flip_sign(-10121234) << endl;

	return 0;
}

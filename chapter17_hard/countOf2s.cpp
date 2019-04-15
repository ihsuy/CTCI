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
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }
template<typename T>
inline void inspect(T& t){typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Count of 25: Write a method to count the number of 2s that 
appear in all the numbers between 0 and n (inclusive).
*/

// brute force
int count2s(int n)
{	// count number of 2s in an integer
	// for the purpose of experiment
	int count = 0;
	while(n)
	{
		if(n%10 == 2)
		{
			count++;
		}
		n /= 10;
	}
	return count;
}

int count2s_under_bf(const int& n)
{
	int result = 0;
	for(int i = 2; i <= n; ++i)
	{
		result += count2s(i);
	}
	return result;
}

// Solution
int count2s_forPowerOf10_under(const int& n)
{	// only work for positive powers of 10
	if(n == 0)
	{
		return 0;
	}

	if(n == 10)
	{
		return 1;
	}

	int tmp = count2s_forPowerOf10_under(n/10);

	return tmp*10 + n/10;
}

int count2s_under(const int& n, unordered_map<int, int>& buffer)
{
	if(n < 10)
	{
		return (n >= 2);
	}

	int base = pow(10, to_string(n).length()-1);

	int sig = n/base;

	int unit_size = buffer[base];

	int result = unit_size;

	int remainder = n%base;

	if(sig > 2)
	{
		result *= sig;
		result += base;
	}
	else if(sig == 2)
	{
		result *= 2;
		result += remainder+1;
	}

	result += count2s_under(remainder, buffer);

	return result;
}

int main()
{
	unordered_map<int, int> buffer;
	// pre calculate 
	for(int i = 10; i < 100000; i *= 10)
	{
		buffer[i] = count2s_forPowerOf10_under(i);
	}

	for (int i = 20000; i < 21234; ++i)
	{
		auto res1 = count2s_under(i, buffer);
		auto res2 = count2s_under_bf(i);

		cout << "number of 2s under: " << i << endl;
		cout << "my result         : " << res1 << '\n';
		cout << "answer            : " << res2 << '\n';

		if(res1 != res2)
		{
			cout << "wrong!\n";
			break;
		}
	}

	cout << "done\n";

	return 0;
}

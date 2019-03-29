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
Factorial Zeros: Write an algorithm which computes
the number of trailing zeros in n factorial.
*/

int factorialZero(const int& n)
{	// trailing zeros are produced by 
	// multiplying 2 and 5 or multiples of them
	// so to count number of trailing zeros is 
	// to count the number of 2s and 5s appeared from 2-n and 
	// take the smaller number.
	// However, since 2 appears much frequently than 5 at any
	// point of time in a monotone increasing integer sequence,
	// we know that we always have enough 2s for the 5s
	// so this problem becomes to simply count the appearance of 5s

	int count = 0;
	for(int i = 2; i <= n; ++i)
	{
		if(i%5 == 0)
		{	// i is multiple of 5
			// count how many more 5s it contains
			int temp = i;
			while(temp%5==0)
			{
				temp /= 5;
				count++;
			}
		}
	}
	return count;
}

int factorialZero_optimal(int n)
{	// directly counting the appearance of multiple of 5s 
	// first count 5s then 25s and 125s...

	int divisor = 5;
	int fives = n/divisor;
	int count = fives;

	while(fives)
	{
		divisor = (divisor<<2)+divisor; // 5^1, 5^2, 5^3...
		
		fives = n/divisor;

		count += fives;
	}

	return count;
}

int main()
{
	const int N = 1000;

	for(int n = 2; n <= N; ++n)
	{
		int res1 = factorialZero(n), res2 = factorialZero_optimal(n);
		cout << n << " method1: factorial contains " << res1 << " trailing zeros.\n";
		cout << n << " method2: factorial contains " << res2 << " trailing zeros.\n";
		if(res1 != res2)
		{
			cout << ">>>>>>>>>>>>>>>>Something Wrong<<<<<<<<<<<<<<<<\n";
		}		
	}

	return 0;
}

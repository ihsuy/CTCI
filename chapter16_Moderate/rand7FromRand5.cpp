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
Rand7 from RandS: Implement a method rand7() given rand5 (). 
That is, given a method that generates a random number between 0 and 4 (inclusive), 
write a method that generates a random number between 0 and 6 (inclusive).
*/

int rand5()
{	// given random number from 0-4
	return rand()%5;
} 

int rand7()
{	// generate random number from 0 - 6 given rand5()
	while(true)
	{
		int r = rand5()*5 + rand5();
		if(r < 21)
		{
			return r%7;
		}
	}
}

int rand7_2()
{	// generate random number from 0 - 6 given rand5()
	while(true)
	{
		int r1 = rand5()*2; // even number between0-9
		int r2 = rand5();
		if(r2 < 4)
		{
			r2%=2;
			if(r1+r2<7)
			{
				return r1+r2;
			}
		}
	}
}

int main()
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	
	map<int, int> count;
	for(int i = 0; i < 500000; ++i)
	{
		int temp = rand7_2();
		count[temp]++;
	}

	for(auto item: count)
	{
		cout << item.first << " " << item.second << '\n';
	}

	return 0;
}

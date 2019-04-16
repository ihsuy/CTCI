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
Kth Multiple: Design an algorithm to find the kth number 
such that the only prime factors are 3, 5, and 7. 
Note that 3, 5, and 7 do not have to be factors, 
but it should not have any other prime factors. 
For example, the first several multiples 
would be (in order) 1, 3, 5, 7, 9, 15, 21.
*/

// brute force

long long g357(const int& a, const int& b, const int& c)
{
	return pow(3, a)*pow(5, b)*pow(7, c);
}

long long kthMultipleOf357(const int& k)
{
	vector<long long> v;
	v.reserve((k+1)*(k+1)*(k+1));

	for(int a = 0; a <= k; ++a)
	{
		for(int b = 0; b <= k; ++b)
		{
			for(int c = 0; c <= k; ++c)
			{
				v.push_back(g357(a, b, c));
			}
		}
	}

	sort(v.begin(), v.end());
	inspect<vector<long long>>(v);
	return v[k-1];
}

int main()
{
	cout << kthMultipleOf357(5) << '\n';

	return 0;
}

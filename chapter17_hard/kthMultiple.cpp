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

// method 1 brute force
long long kthMultipleOf357_bf(const int& k)
{
	vector<long long> v;
	v.reserve((k+1)*(k+1)*(k+1));

	for(int a = 0; a <= k; ++a)
	{
		long long pa = pow(3, a);
		for(int b = 0; b <= k; ++b)
		{
			long long pb = pow(5, b);
			for(int c = 0; c <= k; ++c)
			{
				v.push_back(pa*pb*pow(7,c));
			}
		}
	}

	sort(v.begin(), v.end());
	
	return v[k-1];
}
// method2 
// find the smallest f*x thats larger than previous_result.back()
// where f is one of the factors {3,5,7} and x is one of the previous_results
long long kthMultipleOf357_O2(const int& k)
{
	vector<long long> factors{3, 5, 7};

	vector<long long> results{1};
	for(int i = 1; i < k; ++i)
	{	// find the smallest product thats larger than results.back()
		long long minmax = LLONG_MAX;

		int f_high = 3; // 3 different factors

		for(int j = 0; j < results.size(); ++j)
		{
			for(int f = 0; f < f_high; ++f)
			{
				long long temp_next = factors[f]*results[j];
				if(temp_next > results.back() and temp_next < minmax)
				{
					minmax = temp_next;
					// since the product is f*result[j]
					// f and result are both in ascending order
					// result[j+1] > result[j]
					// thus f_new*result[j+1] > f_new*result[j]
					// and we want f_new*result[j+1] to be smaller than f*result[j]
					// we must have f_new < f
					f_high = f; 
					break;
				}
			}

			if(f_high == 0)
			{	// at this point, 
				// its impossible for f*results[j] to be any smaller
				break;
			}
		}
		results.push_back(minmax);
	}

	inspect<vector<long long>>(results);
	return results[k-1];
}

int main()
{
	//cout << kthMultipleOf357_bf(5) << '\n';
	cout << kthMultipleOf357_O2(100) << '\n';
	return 0;
}

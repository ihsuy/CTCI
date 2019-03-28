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
Parens: Implement an algorithm to print all valid 
(e.g., properly opened and closed) combinations of n pairs of parentheses.
Input: 3
Output: ((())) (()()) (())() ()()()
*/

const string leftBracket = "[";
const string rightBracket = "]";

void parens_helper(const int& lb, const int& rb, const string& prefix)
{	// lb: number left brackets; rb: number right brackets
	if(lb == 0 and rb == 0)
	{	// when there's no more brackets left
		// we've completed prefix
		cout << prefix << '\n';
	}
	else if(lb == 0)
	{
		parens_helper(lb, rb-1, prefix + rightBracket);
	}
	else if(lb == rb)
	{	// when we have same amount of lb and rb on our hands
		// we can only place lb otherwise we will have 1 extra rb 
		// that's not offset
		parens_helper(lb-1, rb, prefix + leftBracket);
	}
	else
	{	// otherwise we could choose to append either one
		parens_helper(lb-1, rb, prefix + leftBracket);
		parens_helper(lb, rb-1, prefix + rightBracket);
	}
}

void parens(const int& n)
{
	parens_helper(n, n, "");
}


int main()
{
	parens(6);

	return 0;
}

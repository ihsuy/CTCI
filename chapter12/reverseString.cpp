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
Reverse String: Implement a function void reverse( char* str)
in C or C++ which reverses a null-terminated string.
*/

char* to_c_str(const string& s)
{
	char* result = new char[s.length()];

	int i = 0;
	for(; i < s.length(); ++i)
	{
		result[i] = s[i];
	}

	result[i] = 0;

	return result;
}

void reverseCString(char* c)
{
	int len = strlen(c);

	int front = 0, back = len-1;

	while(front<back)
	{
		char temp = c[front];
		c[front] = c[back];
		c[back] = temp;

		front++;
		back--;
	}
}

int main()
{
	string s = "crackingthecodinginterview";
	char* c = to_c_str(s);
	printf("Original string: %s\n", c);
	reverseCString(c);
	printf("Reversed string: %s\n", c);
	return 0;
}

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
English Int: Given any integer,
print an English phrase that describes the integer
(e.g., "One Thousand, Two Hundred Thirty Four").
*/

unordered_map<int, string> numberNames
{
	{-1, "Negative"}, {0, ""},
	{1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"},
	{6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"}, {10, "Ten"},
	{11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"}, {14, "Fourteen"}, {15, "Fifteen"},
	{16, "Sixteen"}, {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"},
	{20, "Twenty"}, {30, "Thirty"}, {40, "Forty"}, {50, "Fifty"}, {60, "Sixty"}, {70, "Seventy"},
	{80, "Eighty"}, {90, "Ninety"},
	{100, "Hundred"}, {1000, "Thousand"}, {1000000, "Million"}, {1000000000, "Billion"}
};

const vector<int> lv {1000000000, 1000000, 1000, 100, 10};

void append(string& s, const string& app)
{
	if (s == "")
	{
		s = app;
	}
	else if(app != "")
	{
		s += (' ' + app);
	}
}

string EnglishInt(int n)
{
	if(n == 0)
	{
		return "Zero";
	}

	string result;

	if (n < 0)
	{	// handle negative numbers
		// since English name for negative numbers
		// is just "negative" + its positive version
		append(result, numberNames[-1]);
		n = -n;
	}

	int mag = 0;
	while(n >= 100)
	{
		int temp = (n/lv[mag]);

		if(temp != 0)
		{
			append(result, EnglishInt(temp));
			append(result, numberNames[lv[mag]]);
		}

		n %= lv[mag];
		mag++;
	}

	if (n <= 20)
	{	
		append(result, numberNames[n]);
		return result;
	}

	int tens = (n / 10) * 10; // how many 10s ?

	if (tens != 0)
	{
		append(result, numberNames[tens]);
	}

	int ones = n % 10;

	if (ones != 0)
	{
		append(result, numberNames[ones]);
	}

	return result;
}


int main()
{
	for (int i = INT_MAX-500; i < INT_MAX; ++i)
	{
		cout << EnglishInt(i) << endl;
	}

	cout << EnglishInt(1234567891) << '\n';
	return 0;
}

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
Re-Space: Oh, no! You have accidentally removed all spaces,
punctuation, and capitalization in a lengthy document.
A sentence like "I reset the computer. It still didn't boot!"
became "iresetthecomputeritstilldidntboot': You'll deal with the
punctuation and capitalization later; right now you need to re-insert
the spaces. Most of the words are in a dictionary but a few are not.
Given a dictionary (a list of strings) and the document (a string)'
design an algorithm to unconcatenate the document in a way that minimizes
the number of unrecognized characters.

EXAMPLE:
Input jesslookedjustliketimherbrother
Output: jess looked just like tim her brother (7 unrecognized characters)
*/

int reSpace_helper(const string& line, const int& p, const int& i,
                   unordered_set<string>& dictionary, const string& result)
{
	if (i >= line.length() and p < line.length())
	{
		return reSpace_helper(line, p + 1, p + 2, dictionary, "");

	}
	else if (p >= line.length())
	{

		return 0;
	}
	string word = line.substr(p, i - p + 1);
	cout << word << '\n';
	int len1 = 0;
	if (dictionary.count(line.substr(p, i - p + 1)))
	{
		cout << "match!\n";
		// include this word
		len1 = reSpace_helper(line, p + i + 1, p + i + 2, dictionary, result + " " + word);

	}
	// do not include this word
	auto len2 = reSpace_helper(line, p, i + 1, dictionary, result)+1;

	return min(len1, len2);
}

int main()
{
	unordered_set<string> dictionary
	{
		"looked", "just", "look", "like", "her", "herb", "other", "brother"
	};
	string s = "";
	cout << reSpace_helper("jesslookedjustliketimherbrother", 0, 1, dictionary, s) << '\n';
	cout << s << endl;
	return 0;
}

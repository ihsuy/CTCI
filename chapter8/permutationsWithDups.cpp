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
Permutations with Dups: Write a method to compute all permutations
of a string whose charac- ters are not necessarily unique.
The list of permutations should not have duplicates.
*/

void strSwap(string& s, const int& i, const int& j)
{
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}

void permWithDups_helper(map<char, int>& freqCounter,
                         const int& remain, const string& prefix)
{
	if(remain == 0)
	{	// nothing left to be added
		// prefix is completed
		cout << prefix << endl;
		return;
	}

	for(auto& item : freqCounter)
	{	// for every char-int pair in the freqCounter
		// look for those has at least one char left in freqCounter
		// append each of them to prefix and recurse
		if(item.second > 0)
		{	// item counter should be decremented since it's about to be
			// appended to prefix
			item.second--;
			permWithDups_helper(freqCounter, remain-1, prefix+string(1, item.first));
			// after its done, we add the counter back so it doesn't affect
			// the up coming recursions
			item.second++;
		}
	}
}

void permWithDups(const string& s)
{
	map<char, int> freqCounter;
	for (auto& ch : s)
	{
		freqCounter[ch]++;
	}

	int remain = s.length();

	string prefix;
	permWithDups_helper(freqCounter, remain, prefix);
}

int main()
{
	string s = "aaaaaaaaba";
	permWithDups(s);
	return 0;
}

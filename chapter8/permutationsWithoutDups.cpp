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
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << '\n'; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Permutations without Dups: Write a method to compute
all permutations of a string of unique characters.
*/

void strSwap(string& s, const int& i, const int& j)
{
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}

void permWithoutDups_helper(string& s, const int& i, const int& j)
{	// this method originate from the observation that
	// the permutation of n characters, can be built from
	// picking each letter as head of the new permutation
	// and permute rest of the characters
	if (i == j)
	{
		cout << s << endl;
		return;
	}

	for (int si = i; si < j; ++si)
	{	// the loop and strSwap are replacing the 'head' character
		// with every letter in the string
		strSwap(s, i, si);

		// then find permutations of the rest of the string
		permWithoutDups_helper(s, i + 1, j);

		// swap back after its done
		strSwap(s, i, si);
	}
}

void permWithoutDups(string s)
{
	permWithoutDups_helper(s, 0, s.length() - 1);
}

vector<string> permWithoutDups2(string s)
{	// build from the previous n-1 permutations
	// insert the new character to every postion in
	// all prev permutations
	if (s.length() == 0)
	{
		return vector<string> {""};
	}

	char head = s[0];
	vector<string> result;
	vector<string> prev_perms = permWithoutDups2(s.substr(1));
	for (int i = 0; i < prev_perms.size(); ++i)
	{
		string temp = prev_perms[i];
		if (temp == "")
		{
			result.push_back(string(1, head));
		}
		else
		{
			for (auto j = temp.begin(); j <= temp.end(); ++j)
			{
				string pre = temp.substr(0, j - temp.begin());
				string post = temp.substr(j - temp.begin());
				result.push_back(pre + string(1, head) + post);
			}
		}
	}
	return result;
}

int main()
{
	string s = "123";

	cout << "method1" << '\n';

	permWithoutDups(s);

	cout << "method2" << '\n';
	auto result = permWithoutDups2(s);

	inspect<vector<string>>(result);


	return 0;
}

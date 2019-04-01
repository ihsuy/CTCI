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
Master Mind: The Game of Master Mind is played as follows:
The computer has four slots, and each slot will contain a ball that is red (R),
yellow (V), green (G) or blue (B). For example, the computer might have RGGB
(Slot #1 is red, Slots #2 and #3 are green, Slot #4 is blue).
You, the user, are trying to guess the solution.You might, for example, guess YRGB.
When you guess the correct color for the correct slot, you get a "hit:' If you guess a
color that exists but is in the wrong slot, you get a "pseudo-hit:' Note that a slot
that is a hit can never count as a pseudo-hit.
For exam ple, if the actual solution is RGBY and you guess GGRR, you have one hit
and one pseudo -hit.
Write a method that, given a guess and a solution, returns the number
of hits and pseudo-hits.
*/

pair<int, int> masterMind(const string& solution, const string& guess)
{
	if (solution.length() != guess.length())
	{
		return {0, 0};
	}

	int hit = 0, pseudo_hit = 0;

	// process solution

	unordered_map<char, int> letter_count;

	for (int i = 0; i < solution.length(); ++i)
	{	// if guess is correst increase hitt
		if (solution[i] == guess[i])
		{
			hit++;
		}
		else
		{	// if its not correct store letter count for later use
			// to count pseudo hit
			letter_count[solution[i]]++;
		}
	}

	// count pseudo_hit
	for (int i = 0; i < solution.length(); ++i)
	{	// if it's not a real hit
		// and it has appeared at least once in solution except when it was correct
		if (solution[i] != guess[i] and letter_count[guess[i]] != 0)
		{
			letter_count[guess[i]]--;
			pseudo_hit++;
		}
	}

	return {hit, pseudo_hit};
}


int main()
{
	string solution = "RGBY";
	string guess = "GGRR";

	auto result = masterMind(solution, guess);
	cout << "hit: " << result.first << " pseudo-hit: " << result.second << '\n';

	return 0;
}

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
Shuffle: Write a method to shuffle a deck of cards.
It must be a perfect shuffle-in other words, each of the 52!
permutations of the deck has to be equally likely. Assume that you
are given a random number generator which is perfect.
*/

void myShuffle(vector<int>& deck)
{	// for every card C in deck
	// randomly choose a card RC after (include itself) card C
	// and swap C and RC
	for (int i = 0; i < deck.size(); ++i)
	{
		size_t idx = i + rand() % (deck.size() - i);
		swap(deck[i], deck[idx]);
	}
}

void myShuffle_recursive_helper(vector<int>& deck, const int& i)
{
	if (i == 0)
	{	// completely shuffled
		return;
	}

	// shuffle earlier part
	myShuffle_recursive_helper(deck, i - 1);

	// assume all deck.size() - 1 cards in the deck are shuffled
	// we only need to randomly select a card from the whole deck to swap with
	int idx = rand() % (i + 1); // (i+1) makes i idx ranges from (0, 1) inclusive
	swap(deck[idx], deck[i]);
}

void myShuffle_recursive(vector<int>& deck)
{
	myShuffle_recursive_helper(deck, deck.size() - 1);
}

int main()
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	int decksize = 52;
	vector<int> deck;
	deck.reserve(decksize);

	for (int i = 1; i <= decksize; ++i)
	{
		deck.push_back(i);
	}

	cout << "before shuffle: " << '\n';
	inspect<vector<int>>(deck);
	vector<int> deck_copy = deck;

	myShuffle(deck);
	cout << "after shuffle: " << '\n';
	inspect<vector<int>>(deck);

	myShuffle_recursive(deck_copy);
	cout << "after myShuffle_recursive: " << '\n';
	inspect<vector<int>>(deck_copy);

	return 0;
}

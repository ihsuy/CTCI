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
Word Distance: You have a large text file containing words.
Given any two words, find the shortest distance (in terms of number of words)
between them in the file. If the operation will be repeated many times for
the same file (but different pairs of words),
can you optimize your solution?
*/

// solution O(m+n)
// store word locations outside of the function for future reuse
unordered_map<string, vector<int>> word_locations;
int wordDistance(const string& test_file, const string& word1, const string& word2)
{
	stringstream tokenizer(test_file);
	string word;
	int pos = 0;
	while (tokenizer >> word)
	{	// keep a record for all word locations
		// store them in a "location array" for each word
		word_locations[word].push_back(pos);
		pos++;
	}

	// find the shortest distance for 2 specific words
	int min_dist = INT_MAX;
	int i = 0, j = 0;

	int len1 = word_locations[word1].size();
	int len2 = word_locations[word2].size();

	if(len1 == 0 or len2 == 0)
	{	// if looking for a word that doesn't exist in the text file
		return -1;
	}

	while(i < len1 and j < len2)
	{	// use two indices to iterate through 2 location arrays simultaneously
		// trying to minimize the distance between the location that the indices pointing at.
		// note: the location arrays are already in ascending order
		// if we want to minimize abs(x[i]-y[j]) where x and y are sorted in ascending order
		// will should increment i if x[i] is less than y[j] and increment j vise versa
		// since we want x[i] and y[j] to get closer to each other
		int loc1 = word_locations[word1][i], loc2 = word_locations[word2][j];
		
		if(loc1 < loc2)
		{
			min_dist = min(min_dist, loc2-loc1);
			i++;
		}
		else
		{
			min_dist = min(min_dist, loc1-loc2);
			j++;
		}
	}
	// note the result should be "number of words between word1 and word2"
	return min_dist-1;
}


int main()
{
	string text = "tree anna and but cloud yushi since science golf anna however cloud can fiction";

	string w1 = "anna";
	string w2 = "cloud";

	cout << wordDistance(text, w1, w2) << '\n';

	return 0;
}

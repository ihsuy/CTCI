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
T9: On old cell phones, users typed on a numeric keypad and the 
phone would provide a list of words that matched these numbers. 
Each digit mapped to a set of 0 - 4 letters. Implement an algorithm 
to return a list of matching words, given a sequence of digits. 
You are provided a list of valid words (provided in whatever data 
structure you'd like). The mapping is shown in the diagram below:
123 abc def
456
ghi jkl mno
789
pqrs tuv wxyz
0
*/

struct trieNode
{
	vector<trieNode*> children;
	char val;
	bool isWordEnd;
	trieNode(const char& c, const bool& iwe = false): children(26, nullptr), val(c), isWordEnd(iwe) {}
};

int chtoi(const char& ch)
{
	if(isupper(ch))
	{
		return tolower(ch)-'a';
	}
	else
	{
		return ch-'a';
	}
}

void insert(trieNode* root, const string& word)
{
	auto wlen = word.length();
	int i = 0;
	while(i < wlen)
	{
		int alphval = chtoi(word[i]);

		if(root->children[alphval] == nullptr)
		{
			root->children[alphval] = new trieNode(alphval, (i==wlen-1));
		}
		root = root->children[alphval];
		i++;
	}
}


int main()
{


	return 0;
}

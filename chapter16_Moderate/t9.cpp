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
	if (isupper(ch))
	{
		return tolower(ch) - 'a';
	}
	else
	{
		return ch - 'a';
	}
}

void insert(trieNode* root, const string& word)
{
	auto wlen = word.length();
	int i = 0;
	while (i < wlen)
	{
		int alphval = chtoi(word[i]);

		if (root->children[alphval] == nullptr)
		{
			root->children[alphval] = new trieNode(alphval, (i == wlen - 1));
		}
		root = root->children[alphval];
		i++;
	}
}

bool wordFound(trieNode* root, const string& word)
{
	auto wlen = word.length();
	int i = 0;
	while (i < wlen - 1)
	{
		int alphval = chtoi(word[i]);
		if (root->children[alphval] == nullptr)
		{
			return false;
		}

		root = root->children[alphval];

		i++;
	}

	int alphval = chtoi(word[i]);
	if (root->children[alphval] != nullptr and root->children[alphval]->isWordEnd)
	{
		return true;
	}
	return false;
}

trieNode* wordSearch(trieNode* root, const string& word)
{
	auto upper = word.length() - 1;
	int i = 0;
	int alphval = 0;
	while (i < upper)
	{
		alphval = chtoi(word[i]);

		if (root->children[alphval] == nullptr)
		{
			return nullptr;
		}

		root = root->children[alphval];

		i++;
	}
	alphval = chtoi(word[i]);
	return root->children[alphval];
}

trieNode* loadEnglishWords(const string& addr)
{
	cout << "loading...\n";
	ifstream inputFile(addr);
	if (not inputFile)
	{
		throw runtime_error("Can't open file: " + addr);
	}

	trieNode* trie = new trieNode(0, false);

	string word;

	int count = 0;
	while (inputFile >> word)
	{
		// ignore those words contain invalid characters
		// bool badWord = false;
		// for(auto& ch: word)
		// {
		// 	bool c1 = islower(ch), c2 = isupper(ch);
		// 	if(not c1 and not c2)
		// 	{
		// 		badWord = true;
		// 	}
		// 	else if(c2)
		// 	{
		// 		ch = tolower(ch);
		// 	}
		// }

		// if(badWord)
		// {
		// 	cout << word << endl;
		// 	continue;
		// }

		insert(trie, word);
		count ++;
	}
	cout << "Completed loading " << count << " English words\n\n";
	return trie;
}

unordered_map<char, string> keypad
{
	/*1*/          {'2', "abc"}, {'3', "def"},
	{'4', "ghi"},  {'5', "jkl"}, {'6', "mno"},
	{'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
	/*0*/
};

void extra_match(const string& letters, const int& depth, const int& default_depth,
                 trieNode* engWords, vector<string>& suggestions)
{
	if (depth == 0)
	{
		return;
	}

	auto cur_node = wordSearch(engWords, letters);

	if (depth != default_depth and cur_node != nullptr and cur_node->isWordEnd)
	{
		suggestions.push_back(letters);
	}
	else if (cur_node == nullptr)
	{
		return;
	}

	for (int i = 0; i < 26; ++i)
	{
		extra_match(letters + (char)('a' + i), depth - 1, default_depth, engWords, suggestions);
	}
}

void matchWords(const string& userInput, const int& idx, const string& letters,
                trieNode* engWords, vector<string>& result, const int& extra_depth)
{	// userInput shouldn't be empty string

	auto cur_node = wordSearch(engWords, letters);
	if (letters != "" and cur_node == nullptr)
	{
		return;
	}

	if (idx == userInput.length())
	{
		if (cur_node->isWordEnd)
		{
			result.push_back(letters);
			extra_match(letters, extra_depth, extra_depth, engWords, result);
		}
		else
		{	// if its not word end, suggest slightly longer words
			extra_match(letters, extra_depth, extra_depth, engWords, result);
		}
		return;
	}

	string choices = keypad[userInput[idx]];

	for (int i = 0; i < choices.length(); ++i)
	{
		matchWords(userInput, idx + 1, letters + choices[i], engWords, result, extra_depth);
	}
}

vector<string> autoSuggestion(const string& userInput, trieNode* engWords, const int& extra_depth = 3)
{	
	for(auto& ch : userInput)
	{
		if(ch > '9' or ch < '2')
		{	
			cout << "userInput contains invalid character: " << ch << '\n';
			return {};
		}
	}

	vector<string> suggestions;
	matchWords(userInput, 0, "", engWords, suggestions, extra_depth);
	return suggestions;
}
int main()
{
	auto engWords = loadEnglishWords("/Users/ihsuy/crack/chapter16_Moderate/engWords.txt");

	string input = "46837378464"; // interesting
	auto result = autoSuggestion(input, engWords);
	cout << "user input: " << input << '\n';
	inspect<vector<string>>(result);

	input = "62464342368"; // magnificent
	result = autoSuggestion(input, engWords);
	cout << "user input: " << input << '\n';
	inspect<vector<string>>(result);

	input = "4682";
	result = autoSuggestion(input, engWords);
	cout << "user input: " << input << '\n';
	inspect<vector<string>>(result);
	return 0;
}

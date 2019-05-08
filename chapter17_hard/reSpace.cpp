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

pair<bool, int> canFit(const string& word, const string& doc, const vector<bool>& isTaken)
{
	int upper = doc.length() - word.length() + 1;
	for (int i = 0; i < upper; ++i)
	{
		if (not isTaken[i] and doc[i] == word[0])
		{
			int j1 = i + 1, j2 = 1;
			while (j2 < word.length() and doc[j1] == word[j2])
			{
				j1++; j2++;
			}
			if (j2 == word.length())
			{
				return {true, i};
			}
		}
	}
	return {false, -1};
}

void markTaken(const string& word, const int& p, vector<bool>& isTaken)
{
	for (int i = p; i < p + word.length(); ++i)
	{
		isTaken[i] = true;
	}
}

void FitWords(const vector<string>& dict, const string& doc,
              const int& w,
              const int& len_remain, int& min_remain,
              vector<bool>& isTaken, vector<bool>& res)
{
	if (w == dict.size())
	{
		if (len_remain < min_remain)
		{
			min_remain = len_remain;
			res = isTaken;
		}
		return;
	}

	for (int i = w; i < dict.size(); ++i)
	{
		string current_word = dict[i];
		auto fit_info = canFit(current_word, doc, isTaken);
		if (fit_info.first)
		{
			vector<bool> newIsTaken {isTaken};
			markTaken(current_word, fit_info.second, newIsTaken);

			FitWords(dict, doc, i + 1,
			         len_remain - current_word.length(), min_remain,
			         newIsTaken, res);
		}
		FitWords(dict, doc, i + 1,
		         len_remain, min_remain,
		         isTaken, res);

	}
}

string reSpace(const vector<string>& dict, const string& doc)
{
	int max_len = doc.length(),
	    min_remain = max_len;

	vector<bool> isTaken(max_len, false), res;
	FitWords(dict, doc, 0, max_len, min_remain, isTaken, res);

	inspect<vector<bool>> (res);

	return "";
}

int main()
{
	vector<string> dictionary
	{
		"looked", "just", "look", "like", "her", "other", "brother"
	};
	string s = "jesslookedjustliketimherbrother";
	reSpace(dictionary, s);
	return 0;
}

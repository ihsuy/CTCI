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

pair<bool, int> canFit(const string& word, const string& doc, const vector<int>& isTaken)
{
	int upper = doc.length() - word.length() + 1;
	for (int i = 0; i < upper; ++i)
	{
		if (isTaken[i] == 0 and doc[i] == word[0])
		{
			int j1 = i + 1, j2 = 1;
			while (isTaken[j1] == 0 and j2 < word.length() and doc[j1] == word[j2])
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

void markTaken(const string& word, const int& p, vector<int>& isTaken)
{
	int i = p;
	for (int j = 0; i < p + word.length(); ++i)
	{
		isTaken[i] = word[j++];
	}
	isTaken[p] = -isTaken[p];
	isTaken[i - 1] = -isTaken[i - 1];
}

void FitWords(const vector<string>& dict, const string& doc,
              const int& w,
              const int& len_remain, int& min_remain,
              vector<int>& isTaken, vector<int>& res)
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
			vector<int> newIsTaken {isTaken};
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

	vector<int> isTaken(max_len, 0), res;
	FitWords(dict, doc, 0, max_len, min_remain, isTaken, res);

	string original_str;
	for (int i = 0; i < res.size();)
	{
		if (res[i] == 0)
		{
			if (i != 0)
			{
				original_str += ' ';
			}
			while (res[i] == 0)
			{
				original_str += doc[i];
				i++;
			}
		}
		else if (res[i] < 0)
		{
			if (i != 0)
			{
				original_str += ' ';
			}
			original_str += -res[i++];
			while (i < res.size() and res[i] > 0)
			{
				original_str += res[i++];
			}
			original_str += -res[i++];
		}
		else
		{
			original_str += res[i++];
		}
	}

	return original_str;
}

struct ParseResult
{
	int invalid;
	string parsed;
	bool empty;
	ParseResult(const int& iv, const string& pd)
		: invalid(iv), parsed(pd), empty(false) {}
	ParseResult()
		: invalid(0), parsed(""), empty(true) {}
};

ParseResult split(unordered_set<string>& dictionary,
                  const string& sentence, const int& start,
                  vector<ParseResult>& buffer)
{
	if (not buffer[start].empty)
	{
		return buffer[start];
	}
	if (start >= sentence.length())
	{
		return ParseResult();
	}

	int bestInvalid = INT_MAX;
	string bestParsed, partial;
	int i = start;
	while (i < sentence.length())
	{
		partial += sentence[i];
		int invalid = dictionary.count(partial) == 0 ? partial.length() : 0;
		if (invalid < bestInvalid)
		{
			ParseResult result = split(dictionary, sentence, i + 1, buffer);
			invalid += result.invalid;
			if (invalid < bestInvalid)
			{
				bestInvalid = invalid;
				bestParsed = partial + ' ' + result.parsed;
				if (bestInvalid == 0)
				{
					break;
				}
			}
		}
		i++;
	}
	buffer[start] = ParseResult(bestInvalid, bestParsed);
	return buffer[start];
}

string bestSplit(unordered_set<string>& dictionary, const string& sentence)
{
	vector<ParseResult> buffer(sentence.length(), ParseResult());
	ParseResult result = split(dictionary, sentence, 0, buffer);
	return result.parsed;
}

int main()
{
	vector<string> dictionary
	{
		"brother", "just", "look", "like", "her", "other", "looked"
	};
	string s = "jesslookedjustliketimherbrother";
	cout << reSpace(dictionary, s) << '\n';

	vector<string> dictionary2
	{
		"tall", "spaces", "boot", "not", "did", "removed", "remove",
		"accidentally", "accident", "have", "all", "you", "oh", "no"
	};
	unordered_set<string> dictionary3
	{
		"tall", "spaces", "boot", "not", "did", "removed", "remove",
		"accidentally", "accident", "have", "all", "you", "oh", "no",
		"punctuation", "capital", "capitalize", "capitalization",
		"and", "a", "length", "lengthy", "document", "in"
	};
	string s2 = "ohnoyouhaveaccidentallyremovedallspaces"
	            "punctuationandcapitalizationinalengthydocument";
	cout << bestSplit(dictionary3, s2) << '\n';
	// cout << reSpace(dictionary2, s2) << '\n';
	return 0;
}

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
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Longest Word: Given a list of words, write a
program to find the longest word made of other words in the list.
*/

bool canBuild(const string& word, unordered_set<string>& hasWord)
{
    if(hasWord.count(word))
    {
        return true;
    }

    for (int i = 0; i < word.length(); ++i)
    {
        string left = word.substr(0, i);
        if(hasWord.count(left))
        {
            string right = word.substr(i);
            printf("left(%s), right(%s)\n", left.c_str(), right.c_str());
            return canBuild(right, hasWord);
        }
    }
    return false;
}

string longestWord(vector<string>& words)
{
    sort(words.begin(), words.end(), [](const string & s1, const string & s2)
    {
        return s1.length() > s2.length();
    });

    unordered_set<string> hasWord;
    for(auto& word : words)
    {
        hasWord.insert(word);
    }

    for (auto& word : words)
    {
        hasWord.erase(word);
        if (canBuild(word, hasWord))
        {
            return word;
        }
        hasWord.insert(word);
    }
    return "";
}


int main()
{
    vector<string> words{"ore", "pine", "app", "apple", "store", "cool",
                         "pineapple", "appstore", "coolappstoreisfancy",
                         "is", "not", "fancy"};
    cout << longestWord(words) << '\n';
    return 0;
}

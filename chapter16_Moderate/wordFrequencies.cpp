#include <math.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
inline int two(int n) {
    return 1 << n;
}
inline int test(int n, int b) {
    return (n >> b) & 1;
}
inline void set_bit(int& n, int b) {
    n |= two(b);
}
inline void unset_bit(int& n, int b) {
    n &= ~two(b);
}
inline int last_bit(int n) {
    return n & (-n);
}
inline int ones(int n) {
    int res = 0;
    while (n && ++res)
        n -= n & (-n);
    return res;
}
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Word Frequencies: Design a method to find the frequency of occurrences of
any given word in a book. What if we were running this algorithm multiple times?
*/

int wordFreq_linear(const vector<string>& book, string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    int result = 0;

    for (auto w : book) {
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        if (word == w) {
            result++;
        }
    }

    return result;
}

unordered_map<string, int> counter;
int wordFreq_hashTable(const vector<string>& book,
                       string word,
                       const bool& loaded) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    if (not loaded) {  // load all word counts to counter
        for (auto w : book) {
            transform(w.begin(), w.end(), w.begin(), ::tolower);
            counter[w]++;
        }
    }

    return counter[word];
}

int main() {
    vector<string> book{"Life",      "isn't", "complete", "without",
                        "challenge", "Isn't", "life",     "great"};

    cout << "word \"great\" appeared " << wordFreq_linear(book, "gReAt")
         << " times\n";
    cout << "word \"life\" appeared " << wordFreq_linear(book, "LIFE")
         << " times\n";

    cout << "word \"great\" appeared "
         << wordFreq_hashTable(book, "gReAt", false) << " times\n";
    cout << "word \"life\" appeared " << wordFreq_hashTable(book, "LIFE", true)
         << " times\n";

    return 0;
}

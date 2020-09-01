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
 Living People:
 Given a list of people with their birth and death years,
 implement a method to compute the year with the most number of people alive.
 You may assume that all people were born between 1900 and 2000 (inclusive).
 If a person was alive during any portion of that year, they should be included
 in that year's count. For example, Person (birth =1908, death =1909)
 is included in the counts for both 1908 and 1909.
*/

struct people_record {
    int birth_year;
    int death_year;

    people_record(const int& b, const int& d) : birth_year(b), death_year(d) {}
    people_record(initializer_list<int> list) {
        birth_year = *list.begin();
        death_year = *(list.begin() + 1);
    }
};

pair<int, int> livingPeople(const vector<people_record>& people) {
    vector<int> years(121, 0);

    for (int i = 0; i < people.size(); ++i) {
        years[people[i].birth_year - 1900]++;
        years[people[i].death_year - 1899]--;
    }

    int max_alive = -1;
    int max_year = 0;

    int temp = 0;
    for (int i = 0; i < 101; ++i) {
        temp += years[i];
        if (temp > max_alive) {
            max_alive = temp;
            max_year = i + 1900;
        }
    }
    return {max_alive, max_year};
}

void livingPeople_visualize(const vector<people_record>& people) {
    vector<int> years(120, 0);

    for (int i = 0; i < people.size(); ++i) {
        int low = people[i].birth_year - 1900;
        int high = people[i].death_year - 1900;

        for (int y = low; y <= high; ++y) {
            years[y]++;
        }
    }

    for (int i = 1900; i < 2020; ++i) {
        cout << "year: " << i << " alive: " << years[i - 1900] << '\n';
    }
}

int main() {
    vector<people_record> ppl{{1900, 1980},
                              {1935, 1998},
                              {1916, 2011},
                              {1910, 1977},
                              {1935, 1985},
                              {1920, 1945},
                              {1990, 1999},
                              {1912, 1950},
                              {1906, 1990},
                              {1974, 1998},
                              {1900, 1900},
                              {1921, 1987},
                              {1922, 1976},
                              // {1902, 1981},
                              // {1981, 1981},
                              // {1981, 1981},
                              // {1981, 1981},
                              // {1981, 1981},
                              {1981, 1981},
                              {1982, 2015},
                              {1942, 2010}};
    auto result = livingPeople(ppl);
    cout << "max alive: " << result.first << " at year: " << result.second
         << '\n';
    livingPeople_visualize(ppl);
    return 0;
}

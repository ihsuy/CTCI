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
Baby Names: Each year, the government releases a list of
the 10000 most common baby names and their frequencies
(the number of babies with that name). The only problem with
this is that some names have multiple spellings. For example,
"John" and "Jon" are essentially the same name but would be listed
separately in the list. Given two lists, one of names/frequencies
and the other of pairs of equivalent names, write an algorithm
to print a new list of the true frequency of each name.
Note that if John and Jon are synonyms, and Jon and Johnny are synonyms,
then John and Johnny are synonyms. (It is both transitive and symmetric.)
In the final list, any name can be used as the "real " name.

EXAMPLE Input:
Names: John (15), Jon (12), Chris (13), Kris (4), Christopher (19)
Synonyms: (Jon, John), (John, Johnny), (Chris, Kris), (Chris, Christopher)
Output: John (27), Kris (36)
*/

vector<pair<string, int>> mergeNameFrequencies(const vector<pair<string, int>>& names,
                       const vector<pair<string, string>>& synonyms)
{	// use a hashTable for quick look up of number of person with certain name
	unordered_map<string, int> number_of_person{names.begin(), names.end()};
	// build a graph where names are nodes
	unordered_map<string, unordered_set<string>> graph;

	// construct the graph by inserting each pair of name into the hashmap
	// and also insert reversed pair, 
	// since saying A is synonymous B is equivalent to saying B is synonymous to A
	for (int i = 0; i < synonyms.size(); ++i)
	{
		graph[synonyms[i].first].insert(synonyms[i].second);
		graph[synonyms[i].second].insert(synonyms[i].first);
	}
	// use a hashtable to keep track of all the names that we have seen so far
	// to avoid counting the same names again, as well as detecting loops if exists
	unordered_set<string> seen;

	vector<pair<string, int>> result;

	for (auto& connections : graph)
	{	// only proceed if we've never seen this name so far
		if (seen.count(connections.first) != 0)
		{
			continue;
		}
		// note there's the case when the name is not 
		// provided with corresponding "number of person"
		// in this case set the value to 0
		pair<string, int> tmp{connections.first,
		                      number_of_person.count(connections.first) == 0
		                      ? 0 : number_of_person[connections.first]};
		// do a dfs in the graph
		queue<string> todo;
		todo.push(connections.first);

		seen.insert(connections.first); // mark as seen

		while (not todo.empty())
		{
			auto p = todo.front();
			todo.pop();

			if (graph.count(p) != 0)
			{	// if the name doesn't exist in the first field of the 
				// key_value pairs of the map, its a dead end
				for (auto& name : graph[p])
				{	// check if seen to avoid infinite loop
					if(seen.count(name) == 0)
					{
						todo.push(name);
						seen.insert(name); // mark as seen

						if (number_of_person.count(name) != 0)
						{	
							tmp.second += number_of_person[name];
						}
					}
				}
			}
		}
		result.push_back(tmp);
	}

	return result;
}

int main()
{
	vector<pair<string, int>> name_info
	{
		{"John", 15},
		{"Jon", 12},
		{"Chris", 13},
		{"Kris", 4},
		{"Christopher", 19},
		{"Yushi", 1},
		{"Yuushi", 3},
	};

	vector<pair<string, string>> synonyms
	{
		{"Jon", "John"},
		{"John", "Johnny"},
		{"Chris", "Kris"},
		{"Chris", "Christopher"},
		{"Yushi", "Yuushi"}
	};

	// desired output: John (27), Kris (36)

	auto result = mergeNameFrequencies(name_info, synonyms);

	for (auto& item : result)
	{
		printf("(%s, %d)\n", item.first.c_str(), item.second);
	}

	return 0;
}

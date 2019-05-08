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

*/

pair<int, int> getMin(vector<int>& nodes)
{
    int minval = INT_MAX, k = 0, sz = nodes.size();
    for (int i = 0; i < sz; ++i)
    {
        if (nodes[i] >= 0 and nodes[i] < minval)
        {
            minval = nodes[i], k = i;
        }
    }
    nodes[k] = -1;
    return {k, minval};
}

vector<int> DijkstraShortestPath(const vector<vector<int>>& graph,
                                 const int& sp)
{
    int gsize = graph.size();
    vector<int> nodes(gsize, INT_MAX),
           shortest_paths(gsize, 0);
    nodes[sp] = 0;

    for (int n = gsize; n > 0; --n)
    {
        pair<int, int> m = getMin(nodes);
        int min_i = m.first, min_val = m.second;
        shortest_paths[min_i] = min_val;

        for (int i = 0; i < gsize; ++i)
        {
            int extended_dist = graph[min_i][i] + min_val;
            if (graph[min_i][i] != 0 and extended_dist < nodes[i])
            {
                nodes[i] = extended_dist;
            }
        }
    }
    return shortest_paths;
}



int getMini(vector<bool>& nodeTaken, vector<int>& shortest_paths, const int& sz)
{
    int min_val = INT_MAX, k = 0;
    for (int i = 0; i < sz; ++i)
    {
        if (not nodeTaken[i] and shortest_paths[i] < min_val)
        {
            min_val = shortest_paths[i], k = i;
        }
    }
    nodeTaken[k] = true;
    return k;
}

vector<int> DijkstraShortestPath2(const vector<vector<int>>& graph,
                                  const int& sp)
{
    int gsize = graph.size();

    vector<bool> nodeTaken(gsize, false);
    vector<int> shortest_paths(gsize, INT_MAX);
    shortest_paths[sp] = 0;

    for (int n = 0; n < gsize; ++n)
    {
        auto curmin_i = getMini(nodeTaken, shortest_paths, gsize);
        for (int i = 0; i < gsize; ++i)
        {
            int dist = graph[curmin_i][i] + shortest_paths[curmin_i];
            if (graph[curmin_i][i] and dist < shortest_paths[i])
            {
                shortest_paths[i] = dist;
            }
        }
    }
    return shortest_paths;
}

int main()
{
    vector<vector<int>> graph
    {
        {0, 4,  0, 0,  0,  0,  0, 8,  0},
        {4, 0,  8, 0,  0,  0,  0, 11, 0},
        {0, 8,  0, 7,  0,  4,  0, 0,  2},
        {0, 0,  7, 0,  9,  14, 0, 0,  0},
        {0, 0,  0, 9,  0,  10, 0, 0,  0},
        {0, 0,  4, 14, 10, 0,  2, 0,  0},
        {0, 0,  0, 0,  0,  2,  0, 1,  6},
        {8, 11, 0, 0,  0,  0,  1, 0,  7},
        {0, 0,  2, 0,  0,  0,  6, 7,  0}
    };
    auto res1 = DijkstraShortestPath(graph, 0);
    auto res2 = DijkstraShortestPath2(graph, 0);
    inspect<vector<int>>(res1);
    inspect<vector<int>>(res2);
    return 0;
}

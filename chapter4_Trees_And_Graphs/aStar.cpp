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
Implement the A* search algorithm
*/

const int ndir = 8;
const vector<int> directions { -1, -1, 1, 1, -1, 0, 1, 0, -1};
// const int ndir = 4;
// const vector<int> directions {-1, 0, 1, 0, -1};
struct cell
{
    int parent_r,
        parent_c;
    double f, g;

    cell()
        :   parent_r(-1), parent_c(-1),
            f(ULONG_MAX), g(ULONG_MAX)
    {}

    void updateParam(const int& pr, const int& pc,
                     const double& ff, const double& gg)
    {
        parent_r = pr, parent_c = pc, f = ff, g = gg;
    }
    void updateParents(const int& pr, const int& pc)
    {
        parent_r = pr, parent_c = pc;
    }
};

bool isValid(const int& r, const int& c,
             const vector<vector<int>>& graph)
{
    return (r >= 0) and (r < graph.size()) and
           (c >= 0) and (c < graph[0].size());
}
bool isValid(const pair<int, int>& cl,
             const vector<vector<int>>& graph)
{
    return (cl.first >= 0) and (cl.first < graph.size()) and
           (cl.second >= 0) and (cl.second < graph[0].size());
}

bool isBlocked(const int& r, const int& c,
               const vector<vector<int>>& graph)
{
    return graph[r][c] == 0;
}
bool isBlocked(const pair<int, int>& cl,
               const vector<vector<int>>& graph)
{
    return graph[cl.first][cl.second] == 0;
}

bool isDest(const int& r, const int& c, const pair<int, int>& dest)
{
    return r == dest.first and c == dest.second;
}

double computeH(const int& r, const int& c, const pair<int, int>& dest)
{
    int a = r - dest.first, b = c - dest.second;
    return sqrt(a * a + b * b);
}

vector<pair<int, int>> GeneratePath(const pair<int, int>& dest,
                                    const vector<vector<cell>>& cellsDetail)
{
    vector<pair<int, int>> path;
    int r = dest.first,
        c = dest.second;
    while (cellsDetail[r][c].parent_r != r or cellsDetail[r][c].parent_c != c)
    {
        path.push_back({r, c});
        int pr = cellsDetail[r][c].parent_r,
            pc = cellsDetail[r][c].parent_c;
        r = pr, c = pc;
    }
    path.push_back({r, c});
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> AStarSearch(const vector<vector<int>>& graph,
                                   const pair<int, int>& src,
                                   const pair<int, int>& dest)
{
    if (not isValid(src, graph) or not isValid(dest, graph)
            or isBlocked(src, graph) or isBlocked(dest, graph))
    {
        throw runtime_error("invalid src | dest");
    }
    if (isDest(src.first, src.second, dest))
    {
        return {dest};
    }

    vector<vector<bool>> cellsSeen(graph.size(),
                                    vector<bool>(graph[0].size(), false));
    vector<vector<cell>> cellsDetail(graph.size(),
                                     vector<cell>(graph[0].size(), cell()));

    cellsDetail[src.first][src.second].updateParam(src.first, src.second, 0, 0);

    set<pair<double, pair<int, int>>> todo;
    todo.insert({0, src});

    while (not todo.empty())
    {
        pair<double, pair<int, int>> p = *todo.begin();
        todo.erase(todo.begin());

        int r = p.second.first, c = p.second.second;

        cellsSeen[r][c] = true;

        for (int i = 0; i < ndir; ++i)
        {
            int next_r = r + directions[i],
                next_c = c + directions[i + 1];

            if (isValid(next_r, next_c, graph))
            {
                if (isDest(next_r, next_c, dest))
                {
                    cellsDetail[next_r][next_c].updateParents(r, c);
                    return GeneratePath(dest, cellsDetail);
                }

                if (not cellsSeen[next_r][next_c] and
                        not isBlocked(next_r, next_c, graph))
                {
                    double next_g = cellsDetail[r][c].g + 1,
                           next_f = next_g + computeH(next_r, next_c, dest);
                    if (next_f < cellsDetail[next_r][next_c].f)
                    {
                        cellsDetail[next_r][next_c].updateParam(r, c, next_f, next_g);

                        todo.insert({next_f, {next_r, next_c}});
                    }
                }
            }
        }
    }

    return {};
}

// >>> utilities <<<
vector<vector<int>> GenerateGraph(const int& h, const int& w,
                                  const pair<int, int>& src,
                                  const pair<int, int>& dest,
                                  const int& obstacle_rate = 7)
{
    vector<vector<int>> graph(h, vector<int>(w, 1));
    for (int i = 0; i < h; ++ i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (rand() % obstacle_rate == 0)
            {
                graph[i][j] = 0;
            }
        }
    }
    graph[src.first][src.second] = graph[dest.first][dest.second] = 1;
    return graph;
}

void RenderGraph(vector<vector<int>> graph,
                 const vector<pair<int, int>>& path)
{
    for (int i = 0; i < path.size(); ++i)
    {
        graph[path[i].first][path[i].second] = 2;
    }

    for (int i = 0; i < graph.size(); ++i)
    {
        cout << "|";
        for (int j = 0; j < graph[0].size(); ++j)
        {
            int v = graph[i][j];
            if (v == 0)
            {
                cout << '.';
            }
            else if (v == 1)
            {
                cout << ' ';
            }
            else if (v == 2)
            {
                cout << '#';
            }
        }
        cout << "|\n";
    }
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    // vector<vector<int>> graph
    // {
    //     { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
    //     { 1, 0, 0, 0, 1, 1, 1, 0, 1, 1 },
    //     { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
    //     { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
    //     { 1, 0, 1, 0, 1, 1, 1, 0, 1, 0 },
    //     { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
    //     { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    //     { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
    //     { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    // };

    // graph height, width
    // and avg 1 out of how many cells should be an obstacle
    int h = 50, w = 50, obstacle_rate = 4;
    pair<int, int> src {0, 0}, dest{h - 1, w - 1};
    auto graph = GenerateGraph(h, w, src, dest, obstacle_rate);

    auto path = AStarSearch(graph, src, dest);

    RenderGraph(graph, path);
    if (path.size() == 0)
    {
        cout << "no path found\n";
    }
    return 0;
}

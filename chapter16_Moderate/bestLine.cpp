#include <math.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
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
Best Line: Given a two-dimensional graph with points on it,
find a line which passes the most number of points.
*/

struct point {
    double x;
    double y;
    point(const double& x_coord, const double& y_coord)
        : x(x_coord), y(y_coord) {}

    bool operator==(const point& p) const { return (p.x == x) and (p.y == y); }
};

namespace std {
template <>
struct hash<point> {
    inline size_t operator()(const point& p) const {
        return hash<double>{}(p.x) ^ hash<double>{}(p.y);
    }
};
}  // namespace std

double slope(const point& p1, const point& p2) {
    if (p1.x == p2.x) {
        return INT_MAX;
    }

    return (p1.y - p2.y) / (p1.x - p2.x);
}

double intercept(const double& k, const point& p) {
    return (p.y - k * p.x);
}

unordered_set<point> bestLine(const vector<point>& graph) {
    unordered_map<string, unordered_set<point>> lines;

    for (int i = 0; i < graph.size() - 1; ++i) {
        for (int j = i + 1; j < graph.size(); ++j) {
            double cur_slope = slope(graph[i], graph[j]);
            double cur_intercept = intercept(cur_slope, graph[i]);

            string key = to_string(cur_slope) + to_string(cur_intercept);

            if (not lines.count(key)) {
                lines[key].insert(graph[i]);
                lines[key].insert(graph[j]);
            } else if (not lines[key].count(graph[j])) {
                lines[key].insert(graph[j]);
            }
        }
    }

    unordered_map<string, unordered_set<point>>::iterator result;
    int maxsz = 0;

    for (auto it = lines.begin(); it != lines.end(); it++) {
        if (it->second.size() > maxsz) {
            maxsz = it->second.size();
            result = it;
        }
    }
    return result->second;
}

int main() {
    vector<point> graph{
        point(1, 2), point(1, 3), point(4, 12), point(2, 6), point(4, 3),
        point(1, 9), point(4, 9), point(2, 2),  point(3, 3), point(100, 100),
    };

    auto result = bestLine(graph);

    cout << "Best line: \n";
    for (auto item : result) {
        cout << "(" << item.x << ", " << item.y << ")" << endl;
    }

    return 0;
}

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
    bool visited;
    int name;
    vector<int> neighbours;

    node(const int& n, const vector<int>& nb)
        : visited(false), name(n), neighbours(nb) {}

    void visit() { visited = true; }
};

void graphSummary(const vector<node*>& g) {
    cout << "======Graph Summary======" << endl;
    for (auto i = 0; i < g.size(); ++i) {
        cout << "node name: " << left << setw(5) << g[i]->name
             << "visited: " << left << setw(5)
             << ((g[i]->visited) ? "YES" : "NO") << "neighbours: ";
        for (auto item : g[i]->neighbours) {
            cout << item << " ";
        }
        cout << endl;
    }
}

vector<node*> createGraph(const vector<vector<bool>>& am) {
    vector<node*> my_graph;

    int n_node = am.size();
    for (int i = 0; i < n_node; ++i) {
        vector<int> cnb;
        for (int j = 0; j < n_node; ++j) {
            if (am[i][j]) {
                cnb.push_back(j);
            }
        }
        my_graph.push_back(new node(i, cnb));
    }

    return my_graph;
}

void dfs(vector<node*>& graph, const int& n) {
    graphSummary(graph);

    if (graph[n]->neighbours.size() == 0) {
        graph[n]->visit();
        return;
    }

    graph[n]->visit();

    for (int i = 0; i < graph[n]->neighbours.size(); ++i) {
        if (not graph[graph[n]->neighbours[i]]->visited) {
            dfs(graph, graph[n]->neighbours[i]);
        }
    }
}

void bfs(vector<node*>& graph) {
    queue<int> todo;
    todo.push(0);
    graph[todo.front()]->visit();
    while (not todo.empty()) {
        auto cur_node = todo.front();
        todo.pop();

        for (int i = 0; i < graph[cur_node]->neighbours.size(); ++i) {
            if (not graph[graph[cur_node]->neighbours[i]]->visited) {
                graph[graph[cur_node]->neighbours[i]]->visit();
                todo.push(i);
            }
        }
    }
}

int main() {
    vector<vector<bool>> m = {
        {0, 1, 0, 0, 1, 1}, {0, 0, 0, 1, 1, 0}, {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
    };

    auto g = createGraph(m);
    auto g2 = g;
    // graphSummary(g);

    // dfs(g, 0);

    // graphSummary(g);

    bfs(g2);

    graphSummary(g2);

    return 0;
}
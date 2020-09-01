#include <iostream>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

struct dependency {
    char dep;
    char proj;

    dependency(const char& d, const char& p) : dep(d), proj(p) {}
};

map<char, unordered_set<char>> buildDependencyMap(
    const vector<char>& projects,
    const vector<dependency>& deps) {
    map<char, unordered_set<char>> dm;

    for (auto p : projects) {
        dm[p] = unordered_set<char>();
    }

    for (auto d : deps) {
        dm[d.proj].insert(d.dep);
    }

    return dm;
}

vector<char> buildOrder(vector<char> projects,
                        vector<dependency> dependencies) {
    auto dm = buildDependencyMap(projects, dependencies);
    vector<char> order;

    while (dm.size() != 0) {
        bool buildableFound = false;
        for (auto& item : dm) {
            if (item.second.size() == 0) {
                buildableFound = true;
                order.push_back(item.first);
                for (auto& item2 : dm) {
                    if ((item2.first != item.first) and
                        (item2.second.find(item.first) != item2.second.end())) {
                        item2.second.erase(item.first);
                    }
                }
                dm.erase(item.first);
            }
            if (dm.size() == 0) {
                break;
            }
        }
        if (not buildableFound) {
            return vector<char>();
        }
    }

    return order;
}

// version 2
struct node {
    char name;
    int dep_count;
    vector<node*> outgoings;

    node(const char& n) : name(n), dep_count(0) {}
};

vector<node*> createGraph(const vector<char>& projects,
                          const vector<string>& dependencies) {
    map<char, node*> graph;
    for (int i = 0; i < projects.size(); ++i) {
        graph[projects[i]] = new node(projects[i]);
    }

    for (int i = 0; i < dependencies.size(); ++i) {
        graph[dependencies[i][0]]->outgoings.push_back(
            graph[dependencies[i][1]]);
        graph[dependencies[i][1]]->dep_count++;
    }

    vector<node*> vgraph;
    for (auto item : graph) {
        vgraph.push_back(item.second);
    }
    return vgraph;
}

vector<char> buildOrder2(const vector<char>& projects,
                         const vector<string>& dependencies) {
    vector<char> order;

    vector<node*> graph = createGraph(projects, dependencies);
    queue<node*> todo;

    for (auto item : graph) {
        if (item->dep_count == 0) {
            todo.push(item);
            order.push_back(item->name);
        }
    }

    if (todo.empty()) {
        return vector<char>();
    }

    node* target = todo.front();

    while (not todo.empty()) {
        target = todo.front();
        for (auto i = 0; i < target->outgoings.size(); ++i) {
            target->outgoings[i]->dep_count--;
            if (target->outgoings[i]->dep_count == 0) {
                todo.push(target->outgoings[i]);
                order.push_back(target->outgoings[i]->name);
            }
        }
        todo.pop();
    }
    return order;
}

int main() {
    vector<char> p = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<dependency> d = {dependency('a', 'd'), dependency('f', 'b'),
                            dependency('b', 'd'), dependency('f', 'a'),
                            dependency('d', 'c')};
    vector<char> p2 = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    vector<string> d2 = {"fc", "bf", "fa", "ab", "bh", "be", "ca", "ae"};

    auto o = buildOrder(p, d);
    for (auto item : o) {
        cout << item << " ";
    }
    cout << endl;

    auto o2 = buildOrder2(p2, d2);

    for (auto item : o2) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
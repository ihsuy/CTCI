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
Simulate social networks and
Implement bidirectional breath-first search to find
the shortest path between 2 person
*/

static int global_id = 0;

struct person {
    int id;

    vector<person*> friends;

    person(const int& init_nfriends = 10) : id(global_id) {
        global_id++;
        friends.reserve(init_nfriends);
    }
};

vector<person*> createSocialNetworks(
    const int& nUser /*total number of user in the network*/,
    const int& nfriends /*number of friends each user has*/) {
    vector<person*> users;
    users.reserve(nUser);

    vector<int> idx;
    for (int i = 0; i < nUser; ++i) {
        idx.push_back(i);
    }

    for (int i = 0; i < nUser; ++i) {
        users.push_back(new person(nfriends));
    }

    // randomly select friends for each user

    for (int i = 0; i < nUser; ++i) {
        auto seed =
            chrono::high_resolution_clock::now().time_since_epoch().count();
        shuffle(idx.begin(), idx.end(), default_random_engine(seed));

        int c = 0;
        while (users[i]->friends.size() < nfriends) {
            if (find(users[i]->friends.begin(), users[i]->friends.end(),
                     users[idx[c]]) == users[i]->friends.end()) {
                users[i]->friends.push_back(users[idx[c]]);
            }
            c++;
        }

        auto fs = users[i]->friends.size();
        for (int j = 0; j < fs; ++j) {
            if (find(users[i]->friends[j]->friends.begin(),
                     users[i]->friends[j]->friends.end(),
                     users[i]) == users[i]->friends[j]->friends.end()) {
                users[i]->friends[j]->friends.push_back(users[i]);
            }
        }
    }

    return users;
}

vector<int> getPath(const unordered_map<int, int>& m1,
                    const unordered_map<int, int>& m2,
                    const int& p1,
                    const int& p2,
                    const int& mid) {
    vector<int> path1;
    vector<int> path2;
    cout << mid << endl;
    int temp = mid;
    while (temp != p1) {
        cout << "p1: " << temp << endl;
        path1.push_back(temp);
        temp = m1.at(temp);
    }
    path1.push_back(p1);

    temp = mid;
    while (temp != p2) {
        cout << "p2: " << temp << endl;
        temp = m2.at(temp);
        path2.push_back(temp);
    }

    reverse(path1.begin(), path1.end());

    vector<int> path(path1.size() + path2.size(), 0);
    copy(path1.begin(), path1.end(), path.begin());
    copy(path2.begin(), path2.end(), path.begin() + path1.size());

    return path;
}

vector<int> bidirectionalBFS_findPath(const vector<person*>& socialNetworks,
                                      const int& i1,
                                      const int& i2) {
    person* person1 = socialNetworks[i1];
    person* person2 = socialNetworks[i2];

    unordered_map<person*, bool> visitedBy1;
    unordered_map<person*, bool> visitedBy2;

    unordered_map<int, int> path1;
    unordered_map<int, int> path2;

    queue<person*> todo1;
    queue<person*> todo2;

    todo1.push(person1);
    todo2.push(person2);

    visitedBy1[person1] = true;
    visitedBy2[person2] = true;

    while (not todo1.empty() and not todo2.empty()) {
        person* p1 = todo1.front();
        todo1.pop();

        for (int i = 0; i < p1->friends.size(); ++i) {
            auto cur = p1->friends[i];

            if (not visitedBy1.count(cur)) {
                path1[cur->id] = p1->id;
                visitedBy1[cur] = true;
                todo1.push(cur);
            }

            if (visitedBy2.count(cur)) {  // path is found
                cout << "path1!\n";
                return getPath(path1, path2, i1, i2, cur->id);
            }
        }

        person* p2 = todo2.front();
        todo2.pop();

        for (int i = 0; i < p2->friends.size(); ++i) {
            auto cur = p2->friends[i];

            if (not visitedBy2.count(cur)) {
                path2[cur->id] = p2->id;
                visitedBy2[cur] = true;
                todo2.push(cur);
            }

            if (visitedBy1.count(cur)) {  // path is found
                cout << "path2!\n";

                return getPath(path1, path2, i1, i2, cur->id);
            }
        }
    }

    return {};
}

int main() {
    auto sn = createSocialNetworks(50, 10);

    for (auto& user : sn) {
        cout << "user #" << user->id << ": ";
        for (auto p : user->friends) {
            cout << p->id << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << endl;

    auto p = bidirectionalBFS_findPath(sn, 0, 1);

    inspect<vector<int>>(p);

    return 0;
}

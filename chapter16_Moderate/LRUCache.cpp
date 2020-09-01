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
LRU Cache: Design and build a "least recently used" cache,
which evicts the least recently used item. The cache should map
from keys to values (allowing you to insert and retrieve a value
associated with a particular key) and be initialized with a max size.
When it is full, it should evict the least recently used item.

capacity: 3
insert 1 {1}
insert 2 {2, 1}
get 1 {1, 2}
insert 3 {3, 1, 2}
get 1	{1, 3, 2}
insert 4 {4, 1, 3}
insert 5 {5, 4, 1}

*/

struct LRUCache {
    list<int> LRU_queue;
    int capacity;
    unordered_map<int, list<int>::iterator> elements;

    LRUCache(const int& cap) : capacity(cap) {}

    int getValue(const int& key) {
        if (elements.count(key) == 0) {
            throw runtime_error("key: " + to_string(key) + " doesn't exist.");
        } else {
            auto handle = elements[key];
            int val = *handle;

            LRU_queue.push_front(*handle);
            LRU_queue.erase(handle);

            elements[key] = LRU_queue.begin();

            return val;
        }
    }

    void insert(const int& key, const int& val) {
        if (elements.count(key) == 0) {
            if (LRU_queue.size() == capacity) {
                LRU_queue.erase(prev(LRU_queue.end()));
            }
            LRU_queue.push_front(val);
            elements[key] = LRU_queue.begin();
        } else {
            LRU_queue.erase(elements[key]);
            LRU_queue.push_front(val);
            elements[key] = LRU_queue.begin();
        }
    }

    void printElements() {
        auto ite = LRU_queue.begin();
        for (; ite != LRU_queue.end(); ++ite) {
            cout << *ite << "->";
        }
        cout << "end\n";
    }
};

int main() {
    LRUCache lc(3);
    lc.insert(1, 1);
    lc.printElements();
    lc.insert(2, 2);
    lc.printElements();
    cout << "get 1: " << lc.getValue(1) << '\n';
    lc.printElements();
    lc.insert(3, 3);
    lc.printElements();
    cout << "get 1: " << lc.getValue(1) << '\n';
    lc.printElements();
    lc.insert(4, 4);
    lc.printElements();
    lc.insert(5, 5);
    lc.printElements();
    return 0;
}

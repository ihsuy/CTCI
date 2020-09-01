#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

template <typename key_type, typename val_type>
struct htNode {
    key_type key;
    val_type val;

    htNode(const key_type& k, const val_type& v) : key(k), val(v) {}
};

template <typename key_type, typename val_type>
struct hashTable {
    const int init_capacity = 16;
    int capacity;
    int size_;
    vector<list<htNode<key_type, val_type>*>> table;

    hashTable() : capacity(init_capacity), size_(0) {
        table = vector<list<htNode<key_type, val_type>*>>(init_capacity);
    }

    size_t get_hashValue(const key_type& k);

    htNode<key_type, val_type>* findKey(const int& index, const key_type& k);

    val_type& operator[](const key_type& k);

    void insert(const key_type& k, const val_type& v);

    size_t size() { return size_; }

    void inspect();

    bool needSizingUp() { return (size_ > capacity / 2); }

    void sizeUp();
};

template <typename key_type, typename val_type>
size_t hashTable<key_type, val_type>::get_hashValue(const key_type& k) {
    return ::hash<key_type>()(k) % capacity;
}

template <typename key_type, typename val_type>
val_type& hashTable<key_type, val_type>::operator[](const key_type& k) {
    size_t index = get_hashValue(k);

    htNode<key_type, val_type>* key_ptr = findKey(index, k);

    if (key_ptr == nullptr) {
        if (needSizingUp()) {
            sizeUp();
            index = get_hashValue(k);
        }

        table[index].push_back(new htNode<key_type, val_type>(k, val_type()));
        size_++;

        key_ptr = table[index].back();
    }

    return key_ptr->val;
}

template <typename key_type, typename val_type>
htNode<key_type, val_type>* hashTable<key_type, val_type>::findKey(
    const int& index,
    const key_type& k) {
    auto tar =
        find_if(table[index].begin(), table[index].end(),
                [k](htNode<key_type, val_type>* n) { return (n->key == k); });

    if (tar == table[index].end()) {
        return nullptr;
    }

    return (*tar);
}

template <typename key_type, typename val_type>
void hashTable<key_type, val_type>::inspect() {
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].size() == 0) {
            cout << "empty list\n";
        } else {
            auto table_head = table[i].begin();
            while (table_head != table[i].end()) {
                cout << '(' << (*table_head)->key << ", " << (*table_head)->val
                     << ")->";

                table_head++;
            }
            cout << "null\n";
        }
    }

    cout << "hashTable size: " << size() << " capacity: " << capacity << endl;
}

template <typename key_type, typename val_type>
void hashTable<key_type, val_type>::insert(const key_type& k,
                                           const val_type& v) {}

template <typename key_type, typename val_type>
void hashTable<key_type, val_type>::sizeUp() {
    capacity *= 2;

    vector<list<htNode<key_type, val_type>*>> prev_table = table;

    vector<list<htNode<key_type, val_type>*>> extended_table(capacity);
    table = extended_table;
    size_ = 0;

    // copy everything from the original table to the extended table

    for (int i = 0; i < prev_table.size(); ++i) {
        if (prev_table[i].size() != 0) {
            for (htNode<key_type, val_type>* item : prev_table[i]) {
                (*this)[item->key] = item->val;
            }
        }
    }
}

int main() {
    hashTable<string, int> ht;

    const int nTest = 500;

    for (int i = 0; i < nTest; ++i) {
        ht[(to_string(i) + "th_item")] = i;
    }

    ht.inspect();

    // cout << "testing..." << endl;
    // for(int i = 0; i < nTest; ++i)
    // {
    // 	cout << (to_string(i)+"th_item") << " = "<< ht[(to_string(i)+"th_item")]
    // << '\n';
    // }
    return 0;
}
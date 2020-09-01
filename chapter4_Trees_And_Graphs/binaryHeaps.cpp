#include <exception>
#include <iostream>
#include <vector>
using namespace std;

struct minHeap {
    vector<int> values;
    minHeap(const vector<int>& v) : values(v) { heapify(); }

    void swap_values(const int& pos1, const int& pos2) {
        if (pos1 >= values.size() or pos2 >= values.size()) {
            throw runtime_error("swap_values: invalid index: out of range");
        }

        int temp = values[pos1];
        values[pos1] = values[pos2];
        values[pos2] = temp;
    }

    int parent(const int& i) { return (i - 1) / 2; }

    int left_child(const int& i) { return i * 2 + 1; }

    int right_child(const int& i) { return i * 2 + 2; }

    void push(const int& val) {
        values.push_back(val);
        bubbleUp();
    }

    void pop() {
        swap_values(0, values.size() - 1);
        values.pop_back();
        bubbleDown();
    }

    int get_min() {
        if (values.size() != 0) {
            return values[0];
        }
        throw runtime_error("Fail to get min: Empty Heap");
    }

    void bubbleDown() {
        int curr = 0;

        while (right_child(curr) < values.size()) {
            if (values[left_child(curr)] < values[right_child(curr)]) {
                swap_values(curr, left_child(curr));
                curr = left_child(curr);
            } else {
                swap_values(curr, right_child(curr));
                curr = right_child(curr);
            }
        }
    }

    void bubbleUp() {
        int curr = values.size() - 1;

        while (curr != 0 and values[curr] < values[parent(curr)]) {
            swap_values(curr, parent(curr));
            curr = parent(curr);
        }
    }

    void heapify() {
        vector<int> temp{values};
        values = vector<int>{temp[0]};
        for (int i = 1; i < temp.size(); ++i) {
            push(temp[i]);
        }
    }
};

int main() try {
    minHeap mh(vector<int>{55, 88, 90, 74, 32, 80, 23});
    for (auto item : mh.values) {
        cout << item << " ";
    }
    cout << endl;
    cout << mh.get_min() << endl;
    mh.pop();
    cout << mh.get_min() << endl;
    mh.pop();
    cout << mh.get_min() << endl;
    mh.pop();
    cout << mh.get_min() << endl;
    mh.pop();
    cout << mh.get_min() << endl;
    mh.pop();
    cout << mh.get_min() << endl;
    return 0;
} catch (runtime_error& re) {
    cout << re.what() << endl;
}
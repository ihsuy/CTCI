#include <time.h>

#include <chrono>
#include <iostream>
#include <random>
#include <stack>
using namespace std;

void show_stack(const stack<int>& stk) {
    auto temp = stk;
    while (not temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
    cout << "===" << endl;
}

void sort_stack(stack<int>& stk) {
    // sort the stack using only another stack
    stack<int> buffer;
    int max1, max2 = INT_MIN;
    int range = stk.size();

    while (range != 0) {
        max1 = INT_MIN;
        bool max_removed = false;
        for (int i = 0; i < range; ++i) {
            if (stk.top() == max2 and not max_removed) {
                stk.pop();
                max_removed = true;
                continue;
            } else if (stk.top() > max1) {
                max1 = stk.top();
            }

            buffer.push(stk.top());
            stk.pop();
        }

        if (max2 != INT_MIN) {
            stk.push(max2);
            range--;
        }
        if (max1 != INT_MIN) {
            stk.push(max1);
            range--;
        }

        max2 = INT_MIN;
        max_removed = false;
        while (not buffer.empty()) {
            if (buffer.top() == max1 and not max_removed) {
                buffer.pop();
                max_removed = true;
                continue;
            } else if (buffer.top() > max2) {
                max2 = buffer.top();
            }

            stk.push(buffer.top());
            buffer.pop();
        }
    }
}

void sort_stack2(stack<int>& stk) {
    stack<int> buffer;
    while (stk.size() != 0) {
        if (buffer.size() == 0) {
            buffer.push(stk.top());
            stk.pop();
        } else {
            int temp = stk.top();
            stk.pop();
            while (buffer.size() != 0 and temp < buffer.top()) {
                stk.push(buffer.top());
                buffer.pop();
            }
            buffer.push(temp);
        }
    }
    while (not buffer.empty()) {
        stk.push(buffer.top());
        buffer.pop();
    }
}

int main() {
    srand(time(NULL));
    stack<int> stk;
    for (int i = 0; i < 20000; ++i) {
        stk.push(rand() % 50);
    }
    auto stk2 = stk;

    auto t1 = chrono::high_resolution_clock::now();
    sort_stack(stk);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    cout << "time1: " << chrono::duration_cast<chrono::milliseconds>(t2).count()
         << endl;
    // show_stack(stk);

    t1 = chrono::high_resolution_clock::now();
    sort_stack2(stk2);
    t2 = chrono::high_resolution_clock::now() - t1;
    cout << "time2: " << chrono::duration_cast<chrono::milliseconds>(t2).count()
         << endl;

    // show_stack(stk2);
}
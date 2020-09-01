#include <iostream>
#include <stack>

using namespace std;

class ssqueue {
    stack<int> stackIn;
    stack<int> stackOut;

    void shiftInOut(const bool& InToOut) {
        if (InToOut) {
            while (not stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        } else {
            while (not stackOut.empty()) {
                stackIn.push(stackOut.top());
                stackOut.pop();
            }
        }
    }

   public:
    void add(const int& val) { stackIn.push(val); }

    int remove() {
        shiftInOut(1);

        auto bottom = stackOut.top();
        stackOut.pop();

        return bottom;
    }

    int peek() {
        shiftInOut(1);

        return stackOut.top();
    }

    bool isEmpty() { return (stackIn.size() == 0 and stackOut.size() == 0); }

    void reveal() {
        shiftInOut(0);

        auto tempstack = stackIn;
        cout << "===" << endl;
        for (auto i = 0; i < stackIn.size(); ++i) {
            cout << tempstack.top() << "|";
            tempstack.pop();
        }
        cout << endl;
        cout << "===" << endl;
    }
};

int main() {
    ssqueue sq;
    for (int i = 0; i < 10; ++i) {
        sq.add(i);
    }
    sq.reveal();
    for (int i = 0; i < 10; ++i) {
        sq.remove();
        sq.reveal();
    }

    return 0;
}
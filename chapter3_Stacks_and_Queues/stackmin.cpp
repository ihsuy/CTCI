#include <exception>
#include <iostream>
using namespace std;

class mStack_exception : public exception {
   public:
    string msg;
    mStack_exception(const string& message) : msg(message) {}
    const char* what() const throw() { return msg.c_str(); }
};

struct mNode {
    int val;
    mNode* next;
    int current_min;
    mNode(const int& value, const int& min)
        : val(value), next(nullptr), current_min(min) {}
};

struct mStack {
    mNode* top;

    mStack() : top(nullptr) {}

    void push(const int& val);
    void pop();
    int get_min();
};

void mStack::push(const int& val) {
    if (top == nullptr) {
        top = new mNode(val, val);
    } else {
        mNode* new_item =
            new mNode(val, ((val < top->current_min) ? val : top->current_min));
        new_item->next = top;
        top = new_item;
    }
}

void mStack::pop() {
    if (top == nullptr) {
        throw mStack_exception("Can't pop an empty stack!");
        return;
    }

    mNode* temp = top;
    top = top->next;
    delete temp;
}

int mStack::get_min() {
    if (top != nullptr) {
        return top->current_min;
    }
    throw mStack_exception("There's no element in the stack!");
}

int main() try {
    mStack ms;
    ms.push(5);
    ms.push(6);
    ms.push(3);
    ms.push(7);
    cout << ms.get_min() << endl;
    ms.pop();
    cout << ms.get_min() << endl;
    ms.pop();
    cout << ms.get_min() << endl;
    ms.pop();
    cout << ms.get_min() << endl;

    return 0;
} catch (mStack_exception& me) {
    cout << "Something wrong: " << me.what() << endl;
}
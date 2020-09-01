#include <exception>
#include <iostream>
using namespace std;

class SetOfStack_exception : public exception {
   public:
    const char* message;
    SetOfStack_exception(const char* msg) : message(msg) {}
    const char* what() const throw() { return message; }
};

struct node {
    int val;
    node* next;
    node(const int& value) : val(value), next(nullptr) {}
};

struct SetOfStacks {
    node** stacks;
    int stacks_size;
    const int max_height;
    int current_height;
    SetOfStacks(const int& mh)
        : stacks(new node*[1]),
          stacks_size(1),
          max_height(mh),
          current_height(0) {}

    void push(const int& val);
    void pop();
    void popAt(const int& index);

    void reveal();
};

void SetOfStacks::push(const int& val) {
    if (current_height == 0) {
        stacks[0] = new node(val);
        current_height++;
        return;
    }

    if (current_height != max_height) {
        auto temp = new node(val);
        temp->next = stacks[stacks_size - 1];
        stacks[stacks_size - 1] = temp;
        current_height++;
    } else {
        node** newstacks = new node*[++stacks_size];
        for (int i = 0; i < stacks_size - 1; ++i) {
            newstacks[i] = stacks[i];
        }
        newstacks[stacks_size - 1] = new node(val);
        current_height = 1;

        auto temp2 = stacks;
        stacks = newstacks;
        delete[] temp2;
    }
}

void SetOfStacks::pop() {
    if (stacks_size == 1 and current_height == 0) {
        throw SetOfStack_exception("Can't pop empty SetOfStacks.");
    } else if (current_height != 1) {
        auto temp = stacks[stacks_size - 1];
        stacks[stacks_size - 1] = stacks[stacks_size - 1]->next;
        delete temp;
        current_height--;
    } else {
        if (stacks_size == 1 and current_height == 1) {
            delete stacks[stacks_size - 1];
            stacks = new node*[1];
            stacks[0] = nullptr;
            current_height = 0;
        } else {
            delete stacks[stacks_size - 1];
            auto newstacks = new node*[--stacks_size];

            for (auto i = 0; i < stacks_size; ++i) {
                newstacks[i] = stacks[i];
            }

            current_height = max_height;

            auto temp2 = stacks;
            stacks = newstacks;
            delete[] temp2;
        }
    }
}

void SetOfStacks::popAt(const int& index) {
    if (index >= stacks_size) {
        throw SetOfStack_exception(
            (to_string(index) + "th stack doesn't exist.").c_str());
    }
    if (index == stacks_size - 1) {
        pop();
    } else {
        if (stacks[index]->next != nullptr) {
            auto temp = stacks[index];
            stacks[index] = stacks[index]->next;
            delete temp;
        } else {
            auto newstacks = new node*[--stacks_size];
            int j = 0;
            for (int i = 0; i < stacks_size + 1; ++i) {
                if (i != index) {
                    newstacks[j] = stacks[i];
                    j++;
                }
            }
            auto temp2 = stacks;
            stacks = newstacks;
            delete[] temp2;
        }
    }
}

void SetOfStacks::reveal() {
    for (int sep = 0; sep < max_height; ++sep) {
        cout << "====";
    }
    cout << endl;

    int i = 0;
    for (; i < stacks_size - 1; ++i) {
        cout << "sub-stack #" << i + 1 << ": ";
        for (auto curr = stacks[i]; curr != nullptr; curr = curr->next) {
            cout << curr->val << "|";
        }
        cout << "end" << endl;
    }
    cout << "sub-stack #" << i + 1 << ": ";

    for (auto curr = stacks[i]; curr != nullptr; curr = curr->next) {
        cout << curr->val << "|";
    }
    cout << "end" << endl;
}

int main() try {
    SetOfStacks sos(7);

    for (int i = 0; i < 20; ++i) {
        sos.push(i);
    }
    for (int i = 0; i < 13; ++i) {
        sos.popAt(1);
    }
    sos.reveal();
    return 0;
} catch (SetOfStack_exception& se) {
    cout << "Something wrong: " << se.what() << endl;
}
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

struct node {
    int val;
    node* next;
    node(const int& value) : val(value), next(nullptr) {}
};

node* createLinkedList(const vector<int>& v) {
    node* head = new node(v[0]);
    node* temp = head;

    for (int i = 1; i < v.size(); ++i) {
        temp->next = new node(v[i]);
        temp = temp->next;
    }

    return head;
}

void showLinkedList(node* head) {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->val << "->";
        temp = temp->next;
    }
    cout << "end" << endl;
}

node* loopDetection(node* head) {
    unordered_set<node*> buffer;
    node* curr = head;
    while (curr != nullptr) {
        if (buffer.find(curr) != buffer.end()) {
            return curr;
        }
        buffer.insert(curr);
        curr = curr->next;
    }
    return nullptr;
}

node* loopDetection2(node* head) {
    // use 2 runners
    node* slow = head;
    node* fast = head;

    do {
        slow = slow->next;
        fast = fast->next->next;
    } while (fast != nullptr and fast->next != nullptr and slow != fast);

    if (fast == nullptr or fast->next == nullptr) {
        return nullptr;
    }

    fast = head;

    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    return fast;
}

int main() {
    // create l which intersects with l1
    node* l = new node(1);
    auto temp = l;
    temp->next = new node(2);
    temp = temp->next;
    temp->next = new node(3);
    temp = temp->next;
    temp->next = new node(4);
    auto loop_begin = temp;
    temp = temp->next;
    temp->next = new node(5);
    temp = temp->next;
    temp->next = new node(6);
    temp = temp->next;
    temp->next = new node(7);
    temp = temp->next;
    temp->next = loop_begin;

    // showLinkedList(temp);
    auto lp = loopDetection2(l);
    if (lp != nullptr) {
        cout << lp->val << endl;
        cout << (loop_begin == lp) << endl;
    }
    return 0;
}
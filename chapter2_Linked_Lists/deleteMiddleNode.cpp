#include <iostream>
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

void deleteMiddleNode(node* the_node) {
    node* temp = the_node;
    the_node->val = the_node->next->val;
    the_node->next = the_node->next->next;
    delete temp;
}

int main() {
    node* mylist = createLinkedList(vector<int>{4, 3, 2, 5, 6, 3, 2});
    showLinkedList(mylist);

    node* temp = mylist;
    while (temp->val != 3) {
        temp = temp->next;
    }
    deleteMiddleNode(temp);

    showLinkedList(mylist);
    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct node {
    T val;
    node* next;
    node(const T& value) : val(value), next(nullptr) {}
};

template <typename T>
node<T>* createLinkedList(const vector<T>& v) {
    node<T>* head = new node<T>(v[0]);
    node<T>* temp = head;

    for (int i = 1; i < v.size(); ++i) {
        temp->next = new node<T>(v[i]);
        temp = temp->next;
    }

    return head;
}

template <typename T>
void showLinkedList(node<T>* head) {
    node<T>* temp = head;
    while (temp != nullptr) {
        cout << temp->val << "->";
        temp = temp->next;
    }
    cout << "end" << endl;
}

template <typename T>
bool isPalindrome(node<T>* head) {
    // find length
    int count = 0;
    node<T>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    node<T>* curr = head;

    vector<T> firstHalf;

    while (firstHalf.size() != count / 2) {
        firstHalf.push_back(curr->val);
        curr = curr->next;
    }

    if (count % 2 != 0) {
        curr = curr->next;
    }

    for (int i = firstHalf.size() - 1; i >= 0; --i) {
        if (firstHalf[i] != curr->val) {
            return false;
        }
        curr = curr->next;
    }

    return true;
}

int main() {
    node<char>* l1 =
        createLinkedList(vector<char>{'c', 'a', 't', 'i', 't', 'a', 'c'});
    showLinkedList(l1);

    cout << isPalindrome(l1) << endl;

    return 0;
}
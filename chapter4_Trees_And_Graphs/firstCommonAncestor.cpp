#include <math.h>

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
    int val;
    node* parent;
    node* left;
    node* right;
    node(const int& value)
        : val(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

int left_child(const int& i) {
    return 2 * i + 1;
}

int right_child(const int& i) {
    return 2 * i + 2;
}

node* createBinaryTree(const vector<int>& arr, const int& i, node* p) {
    if (i >= arr.size()) {
        return nullptr;
    }

    node* n = new node(arr[i]);

    n->parent = p;

    n->left = createBinaryTree(arr, left_child(i), n);

    n->right = createBinaryTree(arr, right_child(i), n);

    return n;
}

void show_BST(node* root) {
    if (root == nullptr) {
        cout << "null" << endl;
        return;
    }

    queue<node*> levelnodes;
    levelnodes.push(root);

    int count = 0;
    int h = 1;

    while (not levelnodes.empty()) {
        auto temp = levelnodes.front();
        levelnodes.pop();

        if (count == pow(2, h) - 1) {
            cout << endl;
            h++;
        }
        cout << temp->val << " ";
        count++;

        if (temp->left != nullptr) {
            levelnodes.push(temp->left);
        }
        if (temp->right != nullptr) {
            levelnodes.push(temp->right);
        }
    }
    cout << endl;
}

bool BTfind(node* n1, node* n2) {
    if (n1 == nullptr) {
        return false;
    }

    if (n1 == n2) {
        return true;
    }

    return BTfind(n1->left, n2) or BTfind(n1->right, n2);
}

node* firstCommonAncestor(node* n1, node* nn, node* n2) {
    if (n1 == nullptr or n2 == nullptr) {
        return nullptr;
    }

    if (n1->parent == nullptr or n2->parent == nullptr) {
        return n1;
    }

    if (BTfind(nn, n2)) {
        return n1;
    }

    auto temp = n1;
    n1 = n1->parent;

    if (n1->right == temp) {
        return firstCommonAncestor(n1, n1->left, n2);
    } else {
        return firstCommonAncestor(n1, n1->right, n2);
    }
}

node* FirstCommonAncestor(node* n1, node* n2) {
    return firstCommonAncestor(n1, n1, n2);
}

int main() {
    // create a tree
    node* tree = createBinaryTree(vector<int>{15, 6, 17, 4, 8, 16, 19, 4, 7}, 0,
                                  nullptr);

    show_BST(tree);
    node* rn = new node(10);
    auto v = FirstCommonAncestor(tree->left->left->right, rn);
    cout << ((v == nullptr) ? "null" : to_string(v->val)) << endl;
    // tree->right->left
    return 0;
}
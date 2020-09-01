#include <math.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
    int val;
    node* left;
    node* right;
    node(const int& value) : val(value), left(nullptr), right(nullptr) {}
};

int left_child(const int& i) {
    return 2 * i + 1;
}

int right_child(const int& i) {
    return 2 * i + 2;
}

node* createBinaryTree(const vector<int>& arr, const int& i) {
    if (i >= arr.size()) {
        return nullptr;
    }

    node* n = new node(arr[i]);

    n->left = createBinaryTree(arr, left_child(i));

    n->right = createBinaryTree(arr, right_child(i));

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

int findTreeHeight(node* root) {
    if (root == nullptr) {
        return -1;
    }

    int lenl = findTreeHeight(root->left);

    if (lenl == INT_MIN) {
        return INT_MIN;
    }

    int lenr = findTreeHeight(root->right);

    if (lenr == INT_MIN) {
        return INT_MIN;
    }

    if (abs(lenl - lenr) > 1) {
        return INT_MIN;
    }

    return max(findTreeHeight(root->left), findTreeHeight(root->right)) + 1;
}

bool checkBalanced(node* root) {
    return (findTreeHeight(root) != INT_MIN);
}

int main() {
    // create a tree
    node* tree = createBinaryTree(
        vector<int>{4, 3, 6, 2, 7, 2, 3, 4, 4, 5, 3, 2, 1, 1, 1, 10}, 0);

    node* weird = new node(10);

    weird->left = new node(5);
    weird->right = new node(3);

    weird->left->left = new node(9);
    weird->left->right = new node(8);

    weird->right->right = new node(8);

    show_BST(tree);

    cout << "height: " << findTreeHeight(tree) << endl;

    cout << "Balanced: " << checkBalanced(tree) << endl;

    cout << "weird tree balanced: " << checkBalanced(weird) << endl;

    return 0;
}
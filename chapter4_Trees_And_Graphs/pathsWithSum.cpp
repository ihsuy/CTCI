#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

struct node {
    int val;
    node* left;
    node* right;
    node(const int& value) : val(value), left(nullptr), right(nullptr) {}
};

void search(node* root,
            unordered_multiset<int>& m,
            const int& s,
            int& runningSum,
            int& nPath) {
    if (root == nullptr) {
        return;
    }

    runningSum += root->val;

    auto target = runningSum - s;

    if (m.find(target) != m.end()) {
        nPath += m.count(target);
    }

    if (runningSum == s) {
        nPath++;
    }

    m.insert(runningSum);

    auto temp_rsum = runningSum;
    auto temp_m = m;

    search(root->left, m, s, runningSum, nPath);

    m.erase(runningSum);
    runningSum = temp_rsum;

    search(root->right, m, s, runningSum, nPath);

    m.erase(runningSum);
    runningSum = temp_rsum;
}

int pathsWithSum(node* root, const int& s) {
    unordered_multiset<int> m;
    int nPath = 0;
    int runningSum = 0;

    search(root, m, s, runningSum, nPath);

    return nPath;
}

int main() {
    node* root = new node(10);

    root->left = new node(5);
    root->left->left = new node(3);
    root->left->left->left = new node(3);
    root->left->left->left->right = new node(5);

    root->left->left->right = new node(-2);
    root->left->left->right->right = new node(2);
    root->left->right = new node(1);
    root->left->right->right = new node(2);

    root->right = new node(-3);
    root->right->right = new node(11);
    root->right->right->left = new node(-10);

    cout << pathsWithSum(root, 8) << endl;

    return 0;
}
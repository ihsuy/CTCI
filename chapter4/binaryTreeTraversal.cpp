#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct binaryTreeNode
{
	int val;
	binaryTreeNode* left;
	binaryTreeNode* right;

	binaryTreeNode(const int& value): val(value), left(nullptr), right(nullptr) {}
};

void inOrderTraversal(binaryTreeNode* root)
{
	// visit the left node, then the current node, finally the right node
	if (root != nullptr)
	{
		inOrderTraversal(root->left);
		cout << root->val << endl;
		inOrderTraversal(root->right);
	}
}

void preOrderTraversal(binaryTreeNode* root)
{
	// visit the current node before its child nodes
	if(root != nullptr)
	{
		cout << root->val << endl;
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

void postOrderTraversal(binaryTreeNode* root)
{
	// visit the current node after visting all its child nodes
	if(root != nullptr)
	{
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		cout << root->val << endl;
	}
}

int main()
{
	// create a tree
	binaryTreeNode* root = new binaryTreeNode(10);
	root->left = new binaryTreeNode(5);
	root->left->right = new binaryTreeNode(12);

	root->right = new binaryTreeNode(20);
	root->right->left = new binaryTreeNode(3);
	root->right->left->left = new binaryTreeNode(9);
	root->right->left->right = new binaryTreeNode(18);
	root->right->right = new binaryTreeNode(7);

	cout << "inOrderTraversal:\n";
	inOrderTraversal(root);

	cout << "preOrderTraversal:\n";
	preOrderTraversal(root);

	cout << "postOrderTraversal:\n";
	postOrderTraversal(root);
	return 0;
}
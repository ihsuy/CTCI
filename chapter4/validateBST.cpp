#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
struct node
{
	int val;
	node* left;
	node* right;
	node(const int& value): val(value), left(nullptr), right(nullptr){}
};

int left_child(const int& i)
{
	return 2*i+1;
}

int right_child(const int& i)
{
	return 2*i+2;
}


node* createBinaryTree(const vector<int>& arr, const int& i)
{
	if(i >= arr.size())
	{
		return nullptr;
	}

	node* n = new node(arr[i]);

	n->left = createBinaryTree(arr, left_child(i));

	n->right = createBinaryTree(arr, right_child(i));

	return n;
}

void show_BST(node* root)
{
	if(root == nullptr)
	{
		cout << "null" << endl;
		return;
	}

	queue<node*> levelnodes;
	levelnodes.push(root);

	int count = 0;
	int h = 1;

	while(not levelnodes.empty())
	{
		auto temp = levelnodes.front();
		levelnodes.pop();

		if(count == pow(2, h)-1)
		{
			cout << endl; 
			h++;
		}
		cout << temp->val << " ";
		count ++;

		if(temp->left != nullptr)
		{
			levelnodes.push(temp->left);
		}
		if(temp->right != nullptr)
		{
			levelnodes.push(temp->right);
		}
	}
	cout << endl;
}

int BSTmax(node* root)
{	// assume BST structure and find its max element
	if(root == nullptr)
	{
		return INT_MIN;
	}

	if(root->right != nullptr)
	{
		return BSTmax(root->right);
	}
	else
	{
		return root->val;
	}
}

int BSTmin(node* root)
{	// assume BST structure and find its max element
	if(root == nullptr)
	{
		return INT_MAX;
	}

	if(root->left != nullptr)
	{
		return BSTmax(root->left);
	}
	else
	{
		return root->val;
	}
}

bool isBST(node* root)
{
	if(root == nullptr)
	{
		return true;
	}

	if(root->val < BSTmax(root->left))
	{
		return false;
	}
	if(root->val >= BSTmin(root->right))
	{
		return false;
	}

	return isBST(root->left) and isBST(root->right);
}

bool isBST2(node* root, const int& mi, const int& ma)
{
	if(root == nullptr)
	{
		return true;
	}

	if(root->val <= mi or root->val > ma)
	{
		return false;
	}

	return (isBST2(root->left, mi, root->val) and isBST2(root->right, root->val, ma));
}

int main()
{
	// create a tree
	node* tree = createBinaryTree(vector<int>{15, 6, 17, 4, 8, 16, 19, 4, 7}, 0);

	show_BST(tree);

	cout << isBST(tree) << endl;
	cout << isBST2(tree, INT_MIN, INT_MAX) << endl;

	return 0;
}
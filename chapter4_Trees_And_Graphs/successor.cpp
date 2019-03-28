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
	node* parent;
	node(const int& value): val(value), left(nullptr), right(nullptr), parent(nullptr){}
};

int left_child(const int& i)
{
	return 2*i+1;
}

int right_child(const int& i)
{
	return 2*i+2;
}


node* createBinaryTree(const vector<int>& arr, const int& i, node* head)
{
	if(i >= arr.size())
	{
		return nullptr;
	}

	node* n = new node(arr[i]);

	n->parent = head;

	n->left = createBinaryTree(arr, left_child(i), n);

	n->right = createBinaryTree(arr, right_child(i), n);

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

node* leftMost(node* n)
{
	if(n->left == nullptr)
	{
		return n;
	}

	return leftMost(n->left);
}

node* successor(node* n)
{
	if(n == nullptr)
	{
		return nullptr;
	}

	if(n->right != nullptr)
	{
		return leftMost(n->right);
	}

	node* temp = n;
	n = n->parent;
	while(n != nullptr and n->right != temp)
	{
		temp = n;
		n = n->parent;
	}
	return n;
}




int main()
{
	// create a tree
	node* tree = nullptr;
	tree = createBinaryTree(vector<int>{15, 6, 17, 4, 8, 16, 19, 2, 7},0, tree);

	show_BST(tree);

	cout << successor(tree)->val << endl;

	return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;
        
struct listNode
{
	int val;
	listNode* next;
	listNode(const int& value): val(value), next(nullptr){}
};

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

listNode* binaryTreeToLinkedList(node* root)
{
	listNode* head = new listNode(root->val);
	listNode* h = head;

	queue<node*> level;
	level.push(root);

	while(not level.empty())
	{
		auto temp = level.front();
		level.pop();

		if(temp->left != nullptr)
		{
			h->next = new listNode(temp->left->val);
			h = h->next;
			level.push(temp->left);
		}

		if(temp->right != nullptr)
		{
			h->next = new listNode(temp->right->val);
			h = h->next;
			level.push(temp->right);
		}
	}
	return head;
}

vector<node*> binaryTreeToVector(node* root)
{
	vector<node*> parents;
	vector<node*> newlevel{root};

	vector<node*> result;
	while(newlevel.size() != 0)
	{
		parents = newlevel;
		newlevel = vector<node*>();

		for(auto i = 0; i < parents.size(); ++i)
		{
			if(parents[i]->left != nullptr)
			{
				newlevel.push_back(parents[i]->left);
				result.push_back(parents[i]->left);
			}

			if(parents[i]->right != nullptr)
			{
				newlevel.push_back(parents[i]->right);
				result.push_back(parents[i]->right);
			}
		}
	}
	return result;
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

void show_linkedList(listNode* head)
{
	listNode* temp = head;

	while(temp != nullptr)
	{
		cout << temp->val << "->";
		temp = temp->next;
	}
	cout << "null" << endl;

}

int main()
{
	vector<int> arr {0, 1, 5, 7, 8, 13, 19, 29, 30};
	// first find first 3 nodes in the tree

	auto bst = createBinaryTree(arr, 0);
	show_BST(bst);

	// auto ll = binaryTreeToLinkedList(bst);
	// show_linkedList(ll);

	auto nv = binaryTreeToVector(bst);
	cout << "vector" << endl;
	for(auto item : nv)
	{
		cout << item->val << endl;
	}
	return 0;
}
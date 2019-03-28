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

node* createMinBST(const vector<int>& arr, const int& begin, const int& end)
{
	if(begin > end)
	{
		return nullptr;
	}

	int mid_point = (begin + end)/2;

	node* mid_node = new node(arr[mid_point]);

	mid_node->left = createMinBST(arr, begin, mid_point-1);

	mid_node->right = createMinBST(arr, mid_point+1, end);

	return mid_node;
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
}

int main()
{
	vector<int> arr {0, 1, 5, 7, 8, 13, 19, 29, 30};
	// first find first 3 nodes in the tree

	auto bst = createMinBST(arr, 0, arr.size()-1);
	show_BST(bst);

	return 0;
}
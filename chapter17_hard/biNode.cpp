#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <list>
#include <chrono>
#include <random>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
#include <sstream>
#include <utility>
#include <bitset>
#include <fstream>
#include <string>

typedef long long ll;
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
BiNode: Consider a simple data structure called BiNode,
which has pointers to two other nodes.

public class BiNode
{
	public BiNode node1, node2;
	public int data;
}

The data structure BiNode could be used to represent
both a binary tree
(where nodel is the left node and node2 is the right node)
or a doubly linked list (where nodel is the previous
node and node2 is the next node). Implement a method
to convert a binary search tree (implemented with BiNode)
into a doubly linked list. The values should be kept
in order and the operation should be performed in place
(that is, on the original data structure).
*/

struct BiNode
{
	int val;
	BiNode* left, *right;
	BiNode(const int& v): val(v), left(nullptr), right(nullptr) {}
};

void udpate_and_connect(BiNode*& prev_node, BiNode*& current_node, BiNode* new_node, BiNode*& dll)
{	// update prev_node with current_node
	// and assign new_node to current_node
	prev_node = current_node;
	current_node = new_node;

	// connect current_node with prev_node
	// since in bst prev_node is should be smaller than current_node
	// in the result double linked list it should also looks like
	// *-----------* -> *--------------*
	// | prev_node |    | current_node |
	// *-----------* <- *--------------*
	// so we connect them this way
	current_node->left = prev_node;
	if (prev_node != nullptr)
	{	// be careful when prev_node is nullptr which means
		// we are at the head of the result double linkedlist
		prev_node->right = current_node;
	}
	else
	{	// when prev_node is nullptr we know current_node is the smallest value
		// its also the head of the result double linkedlist
		dll = current_node;
	}
}

BiNode* bst_to_doubleLinkedList(BiNode* root)
{
	BiNode* prev_node = nullptr;
	BiNode* current_node = nullptr;
	BiNode* dll = nullptr;

	// do a in order traverse
	stack<BiNode*> todo;
	todo.push(root);

	while (not todo.empty())
	{
		if (todo.top()->left != nullptr)
		{
			todo.push(todo.top()->left);
		}
		else
		{
			while (not todo.empty() and todo.top()->right == nullptr)
			{	// connect nodes of bst in place
				// since we are at our current_node position now
				// we don't care if we mess with the links on the left hand side
				// of it since we are done with any nodes on the left hand side of it
				udpate_and_connect(prev_node, current_node, todo.top(), dll);
				todo.pop();
			}

			if (todo.empty())
			{
				break;
			}

			auto current_top = todo.top();
			udpate_and_connect(prev_node, current_node, current_top, dll);

			todo.pop();
			todo.push(current_top->right);
		}
	}

	return dll;
}


int main()
{
	BiNode* bst = new BiNode(5);
	bst->left = new BiNode(3);
	bst->left->left = new BiNode(2);
	bst->left->left->left = new BiNode(1);
	bst->left->right = new BiNode(4);

	bst->right = new BiNode(8);
	bst->right->left = new BiNode(6);
	bst->right->left->right = new BiNode(7);
	bst->right->right = new BiNode(9);
	/*
	test case:
				5
			   / \
			  3   8
	         / \ / \
		    2  4 6  9
	       /     \
	      1       7
	*/
	cout << "result double linked list: ";
	auto dll = bst_to_doubleLinkedList(bst);
	while (dll != nullptr)
	{
		cout << dll->val << "->";
		dll = dll->right;
	}
	cout << "null\n";

	return 0;
}

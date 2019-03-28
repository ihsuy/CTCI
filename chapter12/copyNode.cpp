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
Copy Node: Write a method that takes a pointer to a Node
structure as a parameter and returns a complete copy of
the passed in data structure. The Node data structure contains
two pointers to other Nodes.
*/

struct Node
{
	Node* left;
	Node* right;

	int val;

	Node(const int& v): left(nullptr), right(nullptr), val(v) {}

	void connect(Node* l, Node* r)
	{
		left = l;
		right = r;
	}
};

Node* NodeDeepCopy_helper(Node* n, unordered_map<Node*, Node*> getCopy)
{
	if(getCopy.count(n) != 0)
	{	// if this node is already visited
		// just return its stored copy
		return getCopy[n];
	}

	Node* m = new Node(n->val);

	// store the copy
	getCopy[n] = m;

	if (n->left != nullptr)
	{
		m->left = NodeDeepCopy_helper(n->left, getCopy);
	}
	if (n->right != nullptr)
	{
		m->right = NodeDeepCopy_helper(n->right, getCopy);
	}

	return m;
}

Node* NodeDeepCopy(Node* n)
{
	unordered_map<Node*, Node*> getCopy;

	return NodeDeepCopy_helper(n, getCopy);
}

void showNodes_helper(Node* n, unordered_set<Node*>& beenHere)
{
	if (n == nullptr)
	{
		cout << "null\n";
		return;
	}

	beenHere.insert(n);
	cout << "val: " << n->val << '\n';

	cout << "going left..." << endl;
	if (beenHere.count(n->left) == 0)
	{
		showNodes_helper(n->left, beenHere);
	}
	else
	{
		cout << "has been here!\n";
	}

	cout << "returned back at val: " << n->val << "\ngoing right..." << endl;

	if (beenHere.count(n->right) == 0)
	{
		showNodes_helper(n->right, beenHere);
	}
	else
	{
		cout << "has been here!\n";
	}
}

void showNodes(Node* n)
{
	unordered_set<Node*> beenHere;

	showNodes_helper(n, beenHere);
}

int main()
{
	Node* n = new Node(0);

	n->connect(new Node(1), new Node(2));

	n->left->connect(n, new Node(6));
	n->right->connect(new Node(3), new Node(4));

	cout << ">>>>n's content:<<<<\n";
	showNodes(n);

	Node* m = NodeDeepCopy(n);
	cout << ">>>>m's content:<<<<\n";
	showNodes(m);

	// modify n see if it affects m

	n->val = 100;
	n->left->right->val = 31415;
	cout << ">>>n's content:<<<<\n";
	showNodes(n);

	cout << ">>>>m's content:<<<<\n";
	showNodes(m);

	return 0;
}

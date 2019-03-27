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
Rank from Stream: Imagine you are reading in a stream of integers. Periodically,
you wish to be able to look up the rank of a number x (the number of values less than or equal to x).
Implement the data structures and algorithms to support these operations.That is,
implement the method track (in t x), which is called when each number is generated,
and the method getRankOfNumber(int x), which returns the number of values less than or
equal to X (not including x itself).
*/



struct rankNode
{
	int key;
	int rank;

	rankNode* left;
	rankNode* right;
	rankNode* parent;

	rankNode(const int& k, rankNode* p): key(k), rank(0), left(nullptr), right(nullptr), parent(p) {}
};

struct streamRanker
{
private:
	void updateAll(rankNode* root)
	{	// increment rank of every node in the tree with root "root"
		if (root == nullptr)
		{
			return;
		}

		updateAll(root->left);
		root->rank++;
		updateAll(root->right);
	}

	void updateRight(rankNode* n)
	{	// increment all rank of node that has key larger than n->key
		while (n->parent != nullptr)
		{
			if (n->parent != nullptr and n->parent->left == n)
			{
				n = n->parent;
				n->rank++;
				updateAll(n->right);
			}
			else if (n->parent != nullptr)
			{
				n = n->parent;
			}
		}
	}

	void updateRank(rankNode* n, const bool& isLeftNode)
	{	// handle rank updating seperately with respect to
		// the relationship between n and its parent

		if (isLeftNode)
		{	// if n is a left child to its parent
			// n replace its parent's rank in the tree
			// then increment rank for every node larger than n
			n->rank = n->parent->rank;
			updateRight(n);
		}
		else
		{	// if n is a right child to its parent
			// it will certainly get on more rank than its parent
			// and its also necessary to increment rank for all nodes
			// that have larger keys
			n->rank = n->parent->rank + 1;
			updateRight(n);
		}
	}

	rankNode* root;

	// use a unordered_map to track nodes and find their rank
	// in O(1) time
	unordered_map<int, rankNode*> ranks;

public:

	streamRanker(): root(nullptr) {}

	const rankNode* getRoot() const
	{	// return root node so i can traverse and inspect its content
		return root;
	}

	int getRankOfNumber(const int& n)
	{
		if (ranks.count(n) == 0)
		{
			return -1;
		}

		return ranks[n]->rank;
	}

	void track(const int& val)
	{	// create a bst
		if (root == nullptr)
		{
			root = new rankNode(val, nullptr);
		}
		else
		{
			rankNode* temp = root;
			while (temp != nullptr)
			{
				if (val >= temp->key)
				{
					if (temp->right == nullptr)
					{
						temp->right = new rankNode(val, temp);
						updateRank(temp->right, false);
						ranks[val] = temp->right;
						break;
					}
					else
					{
						temp = temp->right;
					}
				}
				else
				{
					if (temp->left == nullptr)
					{
						temp->left = new rankNode(val, temp);
						updateRank(temp->left, true);
						ranks[val] = temp->left;
						break;
					}
					else
					{
						temp = temp->left;
					}
				}
			}
		}
	}
};

void inorderTraverse(const rankNode* root)
{	// inspection
	if (root == nullptr)
	{
		return;
	}

	inorderTraverse(root->left);
	cout << "key: " << root->key << " rank:" << root->rank << '\n';
	inorderTraverse(root->right);
}

int main()
{
	vector<int> v {5, 1, 4, 4, 5, 9, 7, 13, 3, 1, 4, 4, 5, 9, 7, 13, 3};
	streamRanker sr;

	for (int i = 0; i < v.size(); ++i)
	{
		sr.track(v[i]);
	}

	inorderTraverse(sr.getRoot());

	for (int i = 0; i < v.size(); ++i)
	{
		cout << "getrank: " << sr.getRankOfNumber(v[i]) << '\n';
	}
	return 0;
}

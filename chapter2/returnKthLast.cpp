#include <iostream>
#include <vector>
using namespace std;

struct node
{
	int val;
	node* next;
	node(const int& value):val(value), next(nullptr){}
};

node* createLinkedList(const vector<int>& v)
{
	node* head = new node(v[0]);
	node* temp = head;

	for(int i = 1; i < v.size(); ++i)
	{
		temp->next = new node(v[i]);
		temp = temp->next;
	}

	return head;
}

void showLinkedList(node* head)
{
	node* temp = head;
	while(temp != nullptr)
	{
		cout << temp->val << "->";
		temp = temp->next;
	}
	cout << "end" << endl;
}

int kthToTheLast(node* mylist, const int& k)
{
	// create two runners and a counter
	// 2nd will start to run when first runner is k distance away
	node* r1 = mylist;
	node* r2 = mylist;
	int count = 0;
	while(r1 != nullptr)
	{
		if(count < k)
		{
			count ++;
		}
		else
		{
			r2 = r2->next	;
		}
		r1 = r1->next;
	}
	return r2->val;
}

int main()
{
	node* mylist = createLinkedList(vector<int>{6,5,3,7,3,2,7});
	showLinkedList(mylist);
	cout << kthToTheLast(mylist, 2)<< endl;
	return 0;
}
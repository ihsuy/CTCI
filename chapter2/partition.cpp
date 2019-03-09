#include <vector>
#include <iostream>

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

node* partition(node* mylist, const int& val)
{
	node* temp = mylist;
	node* new_head = nullptr;
	node* new_tail = nullptr;
	while(temp != nullptr)
	{
		if(new_head == nullptr)
		{
			new_head = new node(temp->val);
			new_tail = new_head;
		}
		else
		{
			if(temp->val < val)
			{
				node* new_node = new node(temp->val);
				new_node->next = new_head;
				new_head = new_node;
			}
			else
			{
				new_tail->next = new node(temp->val);
				new_tail = new_tail->next;
			}
		}
		temp = temp->next;
	}
	return new_head;
}

int main()
{
	node* mylist = createLinkedList(vector<int>{3, 5, 8, 5, 10, 2 ,1});
	showLinkedList(mylist);

	node* newlist = partition(mylist, 8);
	

	showLinkedList(newlist);
	return 0;
}
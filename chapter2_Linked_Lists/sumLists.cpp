#include <vector>
#include <iostream>
#include <math.h>
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

int lltoi(node* head)
{
	int n = 0;
	node* temp = head;
	int multiplier = 1;
	while(temp != nullptr)
	{
		n += (temp->val)*multiplier;
		multiplier *= 10;
		temp = temp->next;
	}
	return n;
}

int lltoi_forward(node* head)
{
	// find length
	int count = 0;
	node* temp = head;
	while(temp != nullptr)
	{
		temp = temp->next;
		count++;
	}
	int n = 0;
	temp = head;
	int multiplier = pow(10, count-1);
	while(temp != nullptr)
	{
		n += (temp->val)*multiplier;
		multiplier /= 10;
		temp = temp->next;
	}
	return n;
}

node* sumLists(node* head1, node* head2)
{
	vector<int> v3;
	int sum_ = lltoi(head1) + lltoi(head2);
	while(sum_ != 0)
	{
		v3.push_back(sum_%10);
		sum_ /= 10;
	}
	return createLinkedList(v3);
}

node* sumLists_forward(node* head1, node* head2)
{
	int sum_ = lltoi_forward(head1) + lltoi_forward(head2);

	// find sum_ length
	int tempsum = sum_;
	int sumlen = 0;
	while(tempsum != 0)
	{
		tempsum /= 10;
		sumlen++;
	}

	vector<int> v3(sumlen);
	int loc = sumlen-1;
	while(sum_ != 0)
	{
		v3[loc] = (sum_%10);
		sum_ /= 10;
		loc--;
	}
	return createLinkedList(v3);
}

int lllen(node* head)
{
	node* temp = head;
	int count = 0;
	while(temp != nullptr)
	{
		count ++;
		temp = temp->next;
	}
	return count;
}

node* sumLists2(node* head1, node* head2)
{
	node* temp1 = head1;
	node* temp2 = head2;

	int len1 = lllen(head1);
	int len2 = lllen(head2);

	if(len1 < len2)
	{
		temp1 = head2;
		temp2 = head1;
		int templen = len1;
		len1 = len2;
		len2 = templen;
	}

	int carry = 0;
	int sum = 0;
	node* result_head = nullptr;
	node* result_curr = nullptr;

	while(temp1 != nullptr and temp2 != nullptr)
	{
		sum = temp1->val + temp2->val + carry;
		carry = sum/10;
		sum %= 10;

		if(result_head == nullptr)
		{
			result_head = new node(sum);
			result_curr = result_head;
		}
		else
		{
			result_curr->next = new node(sum);
			result_curr = result_curr->next;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	if(carry != 0)
	{
		if(len1-len2 != 0)
		{
			while(temp1 != nullptr)
			{
				sum = temp1->val + carry;
				carry = sum/10;
				sum %= 10;

				result_curr->next = new node(sum);
				result_curr = result_curr->next;

				temp1 = temp1->next;
			}
			if(carry != 0)
			{
				result_curr->next = new node(carry);
			}
		}
		else
		{
			result_curr->next = new node(carry);
		}
	}
	else if(len1-len2 != 0)
	{
		while(temp1 != nullptr)
		{
			result_curr->next = new node(temp1->val);
			result_curr = result_curr->next;
			temp1 = temp1->next;
		}
	}

	return result_head;
}


int main()
{
	node* l1 = createLinkedList(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1});
	node* l2 = createLinkedList(vector<int>{8, 1, 1, 1, 1, 1, 1, 1});
	showLinkedList(l1);
	showLinkedList(l2);
	
	showLinkedList(sumLists(l1, l2));
	showLinkedList(sumLists2(l1, l2));
	return 0;
}
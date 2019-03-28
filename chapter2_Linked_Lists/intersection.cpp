#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;


template<typename T> 
struct node
{
	T val;
	node* next;
	node(const T& value):val(value), next(nullptr){}
};

template<typename T>
node<T>* createLinkedList(const vector<T>& v)
{
	node<T>* head = new node<T>(v[0]);
	node<T>* temp = head;

	for(int i = 1; i < v.size(); ++i)
	{
		temp->next = new node<T>(v[i]);
		temp = temp->next;
	}

	return head;
}

template<typename T>
void showLinkedList(node<T>* head)
{
	node<T>* temp = head;
	while(temp != nullptr)
	{
		cout << temp->val << "->";
		temp = temp->next;
	}
	cout << "end" << endl;
}

template<typename T>
node<T>* intersection(node<T>* head1, node<T>* head2)
{	
	unordered_set<node<T>*> buffer;
	node<T>* curr = head1;
	while(curr != nullptr)
	{
		buffer.insert(curr);
		curr = curr->next;
	}
	curr = head2;
	while(curr != nullptr)
	{
		if(buffer.find(curr) != buffer.end())
		{
			return curr;
		}
		curr = curr->next;
	}
	return nullptr;
}

template<typename T>
node<T>* intersection2(node<T>* head1, node<T>* head2)
{
	// if 2 linkedlist insersects, they must share the same last node
	int len1 = 0;
	int len2 = 0;
	auto curr1 = head1;
	auto curr2 = head2;

	while(curr1->next != nullptr)
	{
		curr1 = curr1->next;
		len1 ++;
	}
	len1++;

	while(curr2->next != nullptr)
	{
		curr2 = curr2->next;
		len2 ++;
	}
	len2++;

	if(curr1 != curr2)
	{
		return nullptr;
	}

	auto longer = (len1 > len2)? head1: head2;
	auto shorter = (len1 > len2)? head2: head1;

	int ahead = abs(len1-len2);
	for(auto i = 0; i < ahead; ++i)
	{
		longer = longer->next;
	}

	for(;;longer = longer->next, shorter = shorter->next)
	{
		if(longer == shorter)
		{
			return longer;
		}
	}
}

int main()
{
	
	node<char>* l1 = createLinkedList(vector<char>{'c', 'a', 't', 'i', 't', 'a', 'c'});
	node<char>* l2 = createLinkedList(vector<char>{'c', 'a', 't', 'i'});
	showLinkedList(l1);
	showLinkedList(l2);
	// create l3 which intersects with l1
	node<char>* curr1 = l1;
	node<char>* l3 = new node<char>('b');
	curr1 = curr1->next->next->next;
	node<char>* temp3 = l3;
	temp3->next = new node<char>('a');
	temp3 = temp3->next;
	temp3->next = new node<char>('o');
	temp3 = temp3->next;
	temp3->next = curr1;
	showLinkedList(l3);
	// node<char>* n1 = intersection(l1, l2);
	// node<char>* n2 = intersection(l1, l3);
	node<char>* n1 = intersection2(l1, l2);
	node<char>* n2 = intersection2(l1, l3);
	if(n1 != nullptr)
	{
		cout << n1->val << endl;
	}
	else
	{
		cout << "nullptr" << endl;
	}
	if(n2 != nullptr)
	{
		cout << n2->val << endl;
	}
	else
	{
		cout << "nullptr" << endl;
	}
	return 0;
}
// Implement a linked list

#include <iostream>

using namespace std;

class Node
{
public:	
	int value;
	Node* next;

	Node(const int& val):value(val), next(nullptr){}
};

class linkedList
{
	int length;
public:
	Node* head;
	linkedList():head(nullptr), length(0){}
	void append(const int& val);
	Node* insert(const int& loc, const int& val);
	Node* rinsert(const int& loc, const int& val);
	void weave(const bool& verbose=true);
	Node* erase(const int& val);
	int size(){return length;}
	void show();
};

void linkedList::append(const int& val)
{
	if(head == nullptr)
	{
		head = new Node(val);
	}
	else
	{
		Node* temp = head;
		while(temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = new Node(val);
	}
	length++;
}

Node* linkedList::insert(const int& loc, const int& val)
{
	if(head == nullptr)
	{
		head = new Node(val);
		length++;
		return head;
	}

	int count = 0;
	Node* temp = head;
	Node* prev;
	while(temp != nullptr)
	{
		if(count == loc)
		{
			if(temp == head)
			{
				head = new Node(val);
				head->next = temp;
				length++;
				return head;
			}
			else
			{
				Node* new_node = new Node(val);
				prev->next = new_node;
				new_node->next = temp;
				length++;
				return new_node;
			}
		}
		count++;
		prev = temp;
		temp = temp->next;
	}
	return nullptr;
}

Node* linkedList::rinsert(const int& pos, const int& val)
{
	if(head == nullptr)
	{
		head = new Node(val);
		length++;
		return head;
	}
	int count = 0;
	Node* temp = head;

	while(count != pos)
	{
		temp = temp->next;
		count ++;
	}
	Node* new_node = new Node(val);
	new_node->next = temp->next;
	temp->next = new_node;
	length++;
	return new_node;
}

Node* linkedList::erase(const int& pos)
{
	Node* temp = head;
	Node* prev;

	int count = 0;
	while(temp != nullptr and count != pos)
	{
		prev = temp;
		temp = temp->next;
		count ++;
	}

	if(temp == head)
	{
		head = temp->next;
		delete temp;
		return head;
	}

	if(temp != nullptr)
	{
		prev->next = temp->next;
	}
	else
	{
		return nullptr;
	}

	delete temp;

	length--;

	return prev->next;
}



void linkedList::weave(const bool& verbose)
{
	if(length%2 != 0)
	{
		if(verbose)
		{ 
			cout << "linkedList must be even size to perform weaving" << endl;
		}
		return;
	}

	int plen = length/2;
	// create runners
	Node* runner = head;
	int save_length = length;

	for(int i = 0; i < plen; ++i)
	{
		runner = runner->next;
	}

	for(int i = 0; i < save_length; i += 2)
	{
		this->rinsert(i, runner->value);
		runner = runner->next;
	}

	for(int i = 0 ; i < save_length/2; ++i)
	{
		this->erase(save_length);
	}

	if(verbose)
	{
		show();
	}
}

void linkedList::show()
{
	Node* temp = head;
	while(temp != nullptr)
	{
		cout << temp->value << "->";
		temp = temp->next;
	}
	cout << "null" << endl;;
}

int main()
{
	linkedList mylist;
	for(int i = 1; i < 17; ++i)
	{
		mylist.append(i);
	}
	mylist.show();
	mylist.weave();
	return 0;
}
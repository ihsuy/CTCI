#include <iostream>
#include <unordered_set>
#include <random>
#include <ctime>
using namespace std;

class Node
{
public:
	int value;
	Node* next;

	Node(const int& val): value(val), next(nullptr) {}
};

class linkedList
{
	int length;
public:
	Node* head;
	linkedList(): length(0), head(nullptr) {}
	void append(const int& val);
	Node* insert(const int& loc, const int& val);
	Node* rinsert(const int& loc, const int& val);
	void weave(const bool& verbose = true);
	Node* erase(const int& val);
	int size() {return length;}
	void show();
};

void linkedList::append(const int& val)
{
	if (head == nullptr)
	{
		head = new Node(val);
	}
	else
	{
		Node* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = new Node(val);
	}
	length++;
}

Node* linkedList::insert(const int& loc, const int& val)
{
	if (head == nullptr)
	{
		head = new Node(val);
		length++;
		return head;
	}

	int count = 0;
	Node* temp = head;
	Node* prev;
	while (temp != nullptr)
	{
		if (count == loc)
		{
			if (temp == head)
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
	if (head == nullptr)
	{
		head = new Node(val);
		length++;
		return head;
	}
	int count = 0;
	Node* temp = head;

	while (count != pos)
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
	while (temp != nullptr and count != pos)
	{
		prev = temp;
		temp = temp->next;
		count ++;
	}

	if (temp == head)
	{
		head = temp->next;
		delete temp;
		return head;
	}

	if (temp != nullptr)
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

void linkedList::show()
{
	Node* temp = head;
	while (temp != nullptr)
	{
		cout << temp->value << "->";
		temp = temp->next;
	}
	cout << "null" << endl;;
}

void remove_dup_withBuffer(linkedList& l)
{
	unordered_set<int> buffer;
	Node* temp = l.head;
	Node* prev;
	while (temp != nullptr)
	{
		if (buffer.find(temp->value) != buffer.end())
		{
			prev->next = temp->next;
			delete temp;
			temp = prev;
		}
		else
		{
			buffer.insert(temp->value);
		}

		prev = temp;
		temp = temp->next;
	}
}

void remove_dup(linkedList& l)
{
	Node* temp = l.head;
	while (temp != nullptr)
	{
		Node* prev = temp;
		Node* curr = temp->next;
		while (curr != nullptr)
		{
			if (curr->value == temp->value)
			{
				prev->next = curr->next;
				delete curr;
				curr = prev;
			}
			prev = curr;
			curr = curr->next;
		}
		temp = temp->next;
	}
}

int main()
{
	linkedList l;
	linkedList l2;
	srand(time(NULL));
	int n = 0;
	for (int i = 0; i < 2000; i++)
	{
		n = rand() % 50;
		l.append(n);
		l2.append(n);
	}
	remove_dup_withBuffer(l);
	l.show();
	remove_dup(l2);
	l2.show();

	return 0;
}
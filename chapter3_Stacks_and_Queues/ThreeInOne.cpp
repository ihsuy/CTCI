#include <iostream>
#include <iomanip>
using namespace std;

// only partially implemented, just to show the idea.

struct tStack
{
	const int default_storage_size = 120;

	int* storage;

	int a_bot, b_bot, c_bot,
	    a_top, b_top, c_top;

	int a_size, 
		b_size, 
		c_size;

	tStack(): storage(new int[default_storage_size])
	{
		a_bot = 0;
		b_bot = default_storage_size/3;
		c_bot = default_storage_size*2/3;

		a_top = a_bot+1;
		b_top = b_bot+1;
		c_top = c_bot+1;

		a_size = 40; 
		b_size = 40;
		c_size = 40;
	}

	int a_pop();
	int b_pop();
	int c_pop();

	void a_push(const int& val);
	void b_push(const int& val);
	void c_push(const int& val);

	int a_peek();
	int b_peek();
	int c_peek();

	bool a_isEmpty();
	bool b_isEmpty();
	bool c_isEmpty();

	void info();

	int size();

	~tStack(){ delete[] storage;}
};



int tStack::a_pop()
{
	if(a_top == a_bot+1)
	{// stack is empty, throw an error (for realistic senario)
		cout << "Fail to pop: stack A is empty" << endl;
		return 0;
	}

	int temp = storage[a_top-1];
	storage[a_top-1] = 0;
	a_top--;
	return temp;
}

int tStack::b_pop()
{
	if(b_top == b_bot+1)
	{// stack is empty, throw an error (for realistic senario)
		cout << "Fail to pop: stack B is empty" << endl;
		return 0;
	}

	int temp = storage[b_top-1];
	storage[b_top-1] = 0;
	b_top--;
	return temp;
}

int tStack::c_pop()
{
	if(c_top == c_bot+1)
	{// stack is empty, throw an error (for realistic senario)
		cout << "Fail to pop: stack C is empty" << endl;
		return 0;
	}

	int temp = storage[c_top-1];
	storage[c_top-1] = 0;
	c_top--;
	return temp;
}

void tStack::a_push(const int& val)
{
	if(a_top == b_bot)
	{//exceeded capacity, double A's size
		cout << "A capacity exceeded, reallocating space... " << a_size << "->" << a_size*2 << endl;

		int* new_storage = new int[a_size*2 + b_size + c_size];

		int nabot = a_bot;
		int nbbot = b_bot+(a_size);
		int ncbot = c_bot+(a_size);


		// copy old stack into the new one
		for(int i = a_bot; i < a_top; ++i)
		{
			new_storage[nabot + i] = storage[i];
		}
		new_storage[b_bot] = val;
		for(int i = b_bot; i < b_top; ++i)
		{
			new_storage[nbbot + i] = storage[i];
		}
		for(int i = c_bot; i < c_top; ++i)
		{
			new_storage[ncbot + i] = storage[i];
		}

		delete[] storage;
		storage = new_storage;

		b_top += a_size;
		c_top += a_size;
		a_bot = nabot;
		b_bot = nbbot;
		c_bot = ncbot;

		a_size *= 2;
	}
	a_top++;
	storage[a_top] = val;
}
// void b_push(cont int& val);
// void c_push(cont int& val);

int tStack::size()
{
	return a_size + b_size + c_size;
}

void tStack::info()
{
	cout << string(80, '=') << endl;
	cout << "tStack info: "<< endl;
	cout << setw(25) << "Total allocated size: " << setw(25) << size() << endl;
	cout << setw(25) << "A allocated size: " << setw(25) << a_size << endl;
	cout << setw(25) << "B allocated size: " << setw(25) << b_size << endl;
	cout << setw(25) << "C allocated size: " << setw(25) << c_size << endl;
	cout << setw(25) << "A size: " << setw(25) << a_top-1 << setw(25) << "from: " << a_bot << endl;
	cout << setw(25) << "B size: " << setw(25) << b_top-b_bot-1 << setw(25) << "from: " << b_bot << endl;
	cout << setw(25) << "C size: " << setw(25) << c_top-c_bot-1 << setw(25) << "from: " << c_bot << endl;

	cout << string(80, '=') << endl;
}


int main()
{
	tStack ts;
	ts.info();
	for(int i = 0; i < 1000; ++i)
	{
		ts.a_push(1);	
	}
	
	ts.info();
	return 0;
}
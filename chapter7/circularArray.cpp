#include <iostream>

using namespace std;

template<typename T>
class circularArray
{
	class iterator;

	T* internal_data;
	int head_pos;
public:
	unsigned int size;

	circularArray(): internal_data(nullptr), head_pos(0), size(0) {}
	circularArray(const initializer_list<T>& l);

	T& operator[](const int& index);

	iterator begin() { return iterator(&internal_data[head_pos], internal_data, &internal_data[size], size); }
	iterator end() { return iterator(&internal_data[(head_pos+size)%size], internal_data, &internal_data[size], size); }

	void rightShift(const int& shift)
	{
		head_pos = (size - (shift)%size)%size;
	}

	void leftShift(const int& shift)
	{
		head_pos = (head_pos + (shift)%size)%size;
	}

};

template<typename T>
circularArray<T>::circularArray(const initializer_list<T>& l)
	: head_pos(0)
{
	internal_data = new T[l.size()];

	auto p = l.begin();
	int i = 0;

	while (p != l.end())
	{
		internal_data[i] = *p;
		p++;
		i++;
	}

	size = l.size();
}

template<typename T>
T& circularArray<T>::operator[](const int& index)
{
	if (index >= size)
	{
		throw out_of_range("index out of range");
	}
	//cout << "(" << head_pos<< ','<< index << ")" << endl; 
	return internal_data[(head_pos + index) % size];
}

template<typename T>
class circularArray<T>::iterator
{
	bool done;
	T* ptr, *begin, *end;
	int size;
public:
	iterator(T* p, T* b, T* e, const unsigned int& sz)
	: done(false), ptr(p), begin(b), end(e), size(sz){}

	iterator(const iterator& ite)
	: done(false), ptr(ite.ptr), begin(ite.begin), end(ite.end), size(ite.size){}

	iterator& operator++()
	{
		ptr++;
		if(ptr == end)
		{
			ptr = begin;
		}

		return *this;
	}

	iterator operator++(int)
	{
		ptr++;
		if(ptr == end)
		{
			ptr = begin;
		}

		return this;
	}

	T& operator*() const
	{
		return *ptr;
	}

	bool operator==(const iterator& ite) const
	{
		return (ptr == ite.ptr);
	}

	bool operator!=(const iterator& ite)
	{
		if(not done){
			done = true;
			return true;
		}
		return (ptr != ite.ptr);
	}

	void update(T* b, T* e, const int& sz)
	{
		begin = b;
		end = e;
		size = sz;
	}
};



int main()
try {
	circularArray<int> ca({1, 2, 3, 4, 5});
	for (int i = 0; i < ca.size; ++i)
	{
		cout << ca[i] << " ";
	}
	cout << endl;

	ca.rightShift(2);

	for (int i = 0; i < ca.size; ++i)
	{
		cout << ca[i] << " ";
	}
	cout << endl;

	ca.leftShift(4);

	for (int i = 0; i < ca.size; ++i)
	{
		cout << ca[i] << " ";
	}
	cout << endl;

	ca.leftShift(3);
	for (auto& item : ca)
	{
		cout << item << " ";
	}
	cout << endl;

	ca.rightShift(1);
	for (auto& item : ca)
	{
		cout << item << " ";
	}
	cout << endl;

	ca.rightShift(2);
	for (auto& item : ca)
	{
		cout << item << " ";
	}
	cout << endl;

	ca.rightShift(3);
	for (auto& item : ca)
	{
		cout << item << " ";
	}
	cout << endl;

	ca.rightShift(4);
	for (auto& item : ca)
	{
		cout << item << " ";
	}
	cout << endl;

	ca.rightShift(5);
	for (auto& item : ca)
	{
		cout << item << " ";
	}
	cout << endl;

	return 0;
}
catch (out_of_range& oor)
{
	cout << oor.what() << endl;
}
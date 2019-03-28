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
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }
template<typename T>
inline void inspect(T& t){typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Smart Pointer: Write a smart pointer class. 
A smart pointer is a data type, usually implemented with templates, 
that simulates a pointer while also providing automatic garbage collection. 
It automatically counts the number of references to a SmartPointer<T* >object
 and frees the object of type T when the reference count hits zero.
*/

template<typename T>
class smartPointer
{
	static unordered_map<T, int> refCounter;

	T ptr;

public:

	smartPointer(T p): ptr(p)
	{
		refCounter[p]++;
	};

	void copy(const smartPointer<T>& obj)
	{
		if(obj.ptr != ptr)
		{
			refCounter[ptr]--;
		}
		else
		{
			refCounter[ptr]++;
		}

		if(refCounter[ptr]==0)
		{
			cout << "removing \"" << *ptr << "\" at address " << ptr << endl;
			delete ptr;
		}

		ptr = obj.ptr;
	}

	void operator=(const T& obj)
	{
		if(obj != ptr)
		{
			refCounter[ptr]--;
		}
		else
		{
			refCounter[ptr]++;
		}

		if(refCounter[ptr]==0)
		{
			cout << "removing \"" << *ptr << "\" at address " << ptr << endl;
			delete ptr;
		}

		ptr = obj;
	}
};

template<typename T>
unordered_map<T, int> smartPointer<T>::refCounter;

int main()
{
	// create two pointers to two different strings
	string* yname = new string("yushi");
	string* aname = new string("Anna");

	smartPointer<string*> name1(yname); // refCounter for yname ++ (0->1)
	smartPointer<string*> name2(yname);	// refCounter for yname ++ (1->2)
	smartPointer<string*> name3(aname); // refCounter for aname ++ (0->1)

	name3.copy(name1); // refCounter for aname -- (1->0): this will cause space held by aname to be released
	
	string* hname = new string("hisaishi"); 
	name1 = hname;	// refCounter for yname -- (2->1)
	name2 = hname;	// refCounter for yname -- (1->0):  this will cause space held by yname to be released
	
	return 0;
}

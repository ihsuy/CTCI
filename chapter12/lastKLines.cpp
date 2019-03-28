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
#include <fstream>

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
Last K Lines: Write a method to print the
last Klines of an input file using C++.
*/

const string addr = "./lastKLines_testFile.txt";

void createSampleFile(const int& nLine)
{	// create a file contains n lines
	// with 1 integer occupying each line
	// see if this file already exist
	ifstream test_open (addr);
	if (test_open)
	{	// remove it if exists
		remove(addr.c_str());
	}
	else
	{
		test_open.close();
	}

	ofstream ofile(addr);
	if (not ofile)
	{
		throw runtime_error("Can't create file: " + addr);
	}

	for (int i = 1; i <= nLine; ++i)
	{
		ofile << i << '\n';
	}

	ofile.close();
}

void printLastKLines(const int& k)
{
	ifstream my_file(addr);
	if (not my_file)
	{
		throw runtime_error("Can't open file: " + addr);
	}

	// use a list to serve as a size K sliding window
	// remove the first node whenever K capacity is reached
	list<string> kLines;

	string line;
	while (my_file >> line)
	{
		kLines.push_back(line);
		if(kLines.size() > k)
		{
			kLines.pop_front();
		}
	}

	// display content of kLines
	for(const auto& item : kLines)
	{
		cout << "line: " << item << '\n';
	}
}

int main()
{
	createSampleFile(1000);

	printLastKLines(100);

	return 0;
}

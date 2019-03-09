#include <iostream>
#include <bitset>
#include <utility>
#include <math.h>
using namespace std;

string itob(const int& num)
{
	bitset<32> bs(num);
	return bs.to_string();
}

int btoi(const string& b)
{
	bitset<32> bs(b);
	return bs.to_ulong();
}

void clearToEnd(int& num, const int& i)
{
	num = ((num>>(i+1))<<(i+1));
}

void setBit(int& num, const int& i)
{
	num = num | (1 << i);
}

void clearBit(int& num, const int& i)
{
	num = num & ~(1<<i);
}

pair<int, int> firstMiddleZero(const int& num)
{
	string n = itob(num);

	int oneCount = 0;

	int i = n.length()-1;

	while(n[i] != '1' and i >= 0)
	{
		i--;
	}

	while(n[i] != '0' and i >= 0)
	{
		oneCount++;
		i--;
	}

	if(i == -1)
	{
		throw runtime_error("this number doesn't contain 0 or contains only 0s in its binary representation.");
	}

	return make_pair(n.length()-1-i, oneCount);
}

pair<int, int> firstMiddleOne(const int& num)
{
	string n = itob(num);

	int oneCount = 0;

	int i = n.length()-1;
	
	while(n[i] != '0' and i >= 0)
	{
		oneCount++;
		i--;
	}

	while(n[i] != '1' and i >= 0)
	{
		i--;
	}

	if(i == -1)
	{
		throw runtime_error("this number doesn't contain 1 or contains one 1s in its binary representation.");
	}

	return make_pair(n.length()-1-i, oneCount);
}

int nextLargerNumber(const int& n)
{
	int num = n;

	auto info = firstMiddleZero(num);
	int loc = info.first;
	int oneCount = info.second;

	setBit(num, loc);
	clearToEnd(num, loc-1);

	int tail = 0;
	for(int i = 0; i < oneCount-1; ++i)
	{
		tail += pow(2, i);
	}

	return num | tail;
}

int nextSmallerNumber(const int& n)
{
	int num = n;

	auto info = firstMiddleOne(num);
	int loc = info.first;
	int oneCount = info.second;

	clearBit(num, loc);
	clearToEnd(num, loc-1);

	int tail = 0;
	for(int i = 0; i < oneCount+1; ++i)
	{
		tail += pow(2, i);
	}

	return num | (tail<<(loc - oneCount - 1));
}

int main()
{
	string n = "10011110000011";
	cout << n << endl;

	cout << itob(nextLargerNumber(btoi(n))) << endl;
	cout << itob(nextSmallerNumber(btoi(n))) << endl;

	return 0;
}
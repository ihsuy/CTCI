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
#include <fstream>
#include <string>

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
Calculator: Given an arithmetic equation
consisting of positive integers, +, -, * and / (no parentheses).
compute the result.
*/

string nextNum(const string& input, int& i)
{
	string num;
	while (i < input.length() and isdigit(input[i]))
	{
		num += input[i];
		i++;
	}

	return num;
}

int calculator(const string& input)
{
	vector<string> component;
	int i = 0;
	while (i < input.length())
	{	// get next number
		component.push_back(nextNum(input, i));

		if (i == input.length())
		{
			break;
		}
		// now input[i] is an operator
		component.push_back(string(1, input[i]));
		i++;
	} 

	for (int i = 1 ; i < component.size();)
	{
		int temp = 0;
		if (component[i] == "*")
		{
			temp = stoi(component[i - 1]) * stoi(component[i + 1]);
			component[i-1] = to_string(temp);
			component.erase(component.begin() + i);
			component.erase(component.begin() + i);
		}
		else if (component[i] == "/")
		{
			temp = stoi(component[i - 1]) / stoi(component[i + 1]);
			component[i-1] = to_string(temp);
			component.erase(component.begin() + i);
			component.erase(component.begin() + i);
		}
		else
		{
			i += 2;
		}
	}

	int result = stoi(component[0]);

	for (int i = 1 ; i < component.size(); i += 2)
	{
		if(component[i] == "+")
		{
			result += stoi(component[i+1]);
		}
		else if(component[i] == "-")
		{
			result -= stoi(component[i+1]);
		}
	}

	return result;
}

int calculator_stack(const string& expression)
{
	
}

int main()
{
	const string expression = "1+2*3/4-5+123124*2-1234/2*2";

	cout << calculator(expression) << '\n';

	return 0;
}

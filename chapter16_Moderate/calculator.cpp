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



string nextNum(const string& expression, int& i)
{
	string num;
	while (i < expression.length() and isdigit(expression[i]))
	{
		num += expression[i];
		i++;
	}

	return num;
}


// method 1 use a vector
int calculator(const string& expression)
{
	vector<string> component;

	int i = 0;

	// parse the expression to a vector contains components of it
	// for instance: "1+3" -> {"1", "+", "3"} 
	while (i < expression.length())
	{	// get next number
		component.push_back(nextNum(expression, i));

		if (i == expression.length())
		{
			break;
		}
		// now expression[i] is an operator
		component.push_back(string(1, expression[i]));
		i++;
	}

	// then perform mulplication and division
	// store the results in the same vector
	for (int i = 1 ; i < component.size();)
	{
		int temp = 0;
		if (component[i] == "*")
		{
			temp = stoi(component[i - 1]) * stoi(component[i + 1]);
			component[i - 1] = to_string(temp);
			component.erase(component.begin() + i);
			component.erase(component.begin() + i);
		}
		else if (component[i] == "/")
		{
			temp = stoi(component[i - 1]) / stoi(component[i + 1]);
			component[i - 1] = to_string(temp);
			component.erase(component.begin() + i);
			component.erase(component.begin() + i);
		}
		else
		{
			i += 2;
		}
	}

	// lastly, perform plus and minus
	int result = stoi(component[0]);

	for (int i = 1 ; i < component.size(); i += 2)
	{
		if (component[i] == "+")
		{
			result += stoi(component[i + 1]);
		}
		else if (component[i] == "-")
		{
			result -= stoi(component[i + 1]);
		}
	}

	return result;
}

enum operators
{
	PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/'
};

int priority(const operators& op)
{
	switch (op)
	{
	case PLUS: case MINUS:
		return 0;
	case MULTIPLY: case DIVIDE:
		return 1;
	}
	throw runtime_error("priority: invalid operator");
}

int calculate(const int& n1, const int& n2, const operators& o)
{	// calculate n2 o n1 (note that n2 goes first)
	int result = n2;
	switch (o)
	{
	case PLUS:
		result += n1;
		break;
	case MINUS:
		result -= n1;
		break;
	case MULTIPLY:
		result *= n1;
		break;
	case DIVIDE:
		result /= n1;
		break;
	default:
		throw runtime_error("calculate: invalid operator");
	}
	return result;
}

// method 2, uses 2 stacks
void colapse_2(stack<int>& num, stack<operators>& op)
{
	int n1 = num.top();
	num.pop();
	int n2 = num.top();
	num.pop();

	operators o = op.top();
	op.pop();

	num.push(calculate(n1, n2, o));
}

int colapse_all(stack<int>& num, stack<operators>& op)
{
	while (not (num.size() == 1))
	{
		colapse_2(num, op);
	}
	return num.top();
}

int calculator_stack(const string& expression)
{
	stack<int> num;
	stack<operators> op;

	for (int i = 0; i < expression.length();)
	{
		string nextN = nextNum(expression, i);
		num.push(stoi(nextN));

		if (i == expression.length())
		{	// no more expression
			// colapse stack
			return colapse_all(num, op);
		}

		// expression[i] is now an operator
		if (op.size() == 0)
		{
			op.push(operators(expression[i]));
		}
		else if (priority(operators(expression[i])) > priority(op.top()))
		{
			op.push(operators(expression[i]));
		}
		else
		{
			colapse_2(num, op);

			op.push(operators(expression[i]));
		}

		i++;
	}

	throw runtime_error("calculator_stack: incorrectly formatted expression.");
}

int main()
{
	const string expression = "1+2*321*3/4-45+112423124*2-1234/2*2";

	cout << calculator(expression) << '\n';
	cout << calculator_stack(expression) << '\n';

	return 0;
}

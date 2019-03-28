/*
Implement a method to perform basic string compression using the counts
 of repeated characters. 
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;

string stringCompression(const string& s)
{
	vector<char> uniq;
	vector<int> counter;

	string ans;
	ans.reserve(s.length());

	int count = 1;
	for(int i = 1; i < s.length(); ++i)
	{
		if(s[i-1] != s[i])
		{
			ans += string(1, s[i-1]);
			ans += to_string(count);
			count = 1;
		}
		else
		{
			count ++;
		}
		if(i == s.length()-1)
		{
			ans += string(1, s[i]);
			ans += to_string(count);
		}
	}

	if(ans.length() == s.length())
	{
		return s;
	}
	return ans;
}

int main()
{
	cout << "Enter the string to be compressed: ";
	string my_str;
	cin >> my_str;
	cout << "Result: " << stringCompression(my_str) << endl;
	return 0;
}
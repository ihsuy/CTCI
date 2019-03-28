/*
Palindrome Permutation: Given a string, write a function 
to check if it is a permutation of a palindrome.
*/

#include <iostream>
#include <string>

using namespace std;

bool isPermutationOfPalindrome(const string& s)
{
	int len = s.length();
	const int max_char = 128;
	char char_map[max_char] = {0};
	int odd = 0;
	for(auto item : s)
	{
		if(item != ' ')
		{
			char_map[(int)item]++;
		}
		else
		{
			len--;
		}
	}
	for(int i = 0; i < max_char; ++i)
	{
		if(char_map[i]%2 != 0)
		{
			odd++;
		}
	}
	if(len%2==1 and odd==1)
	{
		return true;
	}
	else if(odd == 0)
	{
		return true;
	}
	return false;
}

int main()
{
	string my_str;
	cout << "Enter a string to check if it's a permutation of a palindrome" << endl;
	getline(cin, my_str);
	if(isPermutationOfPalindrome(my_str))
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl; 
	}
	return 0;
}
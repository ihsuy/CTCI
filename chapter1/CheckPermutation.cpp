/*
Check Permutation: Given two strings, write a method to decide if one
is a permutation of the other.
*/

#include <iostream>
#include <string>

using namespace std;

bool isPermutationOfEachOther(const string& s1, const string& s2)
{	
	auto len1 = s1.length();
	auto len2 = s2.length();

	// it's obvious that 2 strings need to have the same size
	// in order to be permutations of each other
	if(len1 != len2)
	{
		return false;
	}

	// Becareful here, C++ (some compilers) allows string to 
	// hold char that has negative values, though it usually
	// don't make much sense. 
	// Here I'm considering only when negative isn't contained 
	// in the input.
	const int max_char = 128;

	short char_map[max_char] = {0};

	for(auto& item : s1)
	{
		char_map[(int)item]++;
	}
	
	// this process can be thinking as:
	// "remove letters from s1 one by one if the letter in s2
	//  is containted in s1, and return false if it's not." 	
	for(auto& item : s2)
	{
		short & temp = char_map[(int)item];

		if(temp != 0)
		{
			temp--;
		}
		else
		{
			return false;
		}
	}

	return true;
}

int main()
{
	string s1, s2;
	cout << "Check Permutation\nEnter your first string: ";
	getline(cin, s1);
	cout << "Enter your second string: ";
	getline(cin, s2); 

	if(isPermutationOfEachOther(s1, s2))
	{
		cout << s1 << " and " << s2 << " are permutations of each other!" << endl;
	}
	else
	{
		cout << s1 << " and " << s2 << " are NOT permutations of each other!" << endl;
	}

	return 0;
}
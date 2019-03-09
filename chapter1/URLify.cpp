/*
URLify: Write a method to replace all spaces in a string with
'%20'. You may assume that the string has sufficient space at
the end to hold the addtional characters, and that you are given
the "true" length of the string.
*/

#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string URLify_ss(const string& my_str)
{
	stringstream washer(my_str);

	string ans, token;;

	// use (washer >> token) as while condition
	// can prevent "fail to assign value to token (silent bug)"
	// when there's trailing whitespaces at the end,
	// since stringstream, after spitting out the last non-space
	// token, doesn't realize there's no more meaningful content
	// in its buffer, so washer.eof() is false. but continue reading
	// from stringstream to token will cause it to realize it has no
	// more content, and then fail to do so, which will calse token
	// to be unassigned.
	while(washer >> token)
	{
		ans += token + "%20";
	}
	return ans.substr(0, ans.length()-3);
}

void URLify_arr(char* charr, int len)
{
	int num_space = 0;

	for(int i = 0; i < len; ++i)
	{
		if(charr[i]==' ')
		{
			num_space++;
		}
	}

	// key is to do this from backward
	int full_len = len + num_space*2;

	int j = full_len-1;

	for(int i = len-1; i >= 0; --i)
	{
		if(charr[i] != ' ')
		{
			charr[j] = charr[i];
			j--;
		}
		else
		{
			charr[j--]='0';
			charr[j--]='2';
			charr[j--]='%';
		}
	}
}

int main()
{
	string my_str;

	int len;

	getline(cin, my_str);

	cin >> len;

	cout << "URLify_ss: " << URLify_ss(my_str) << endl;

	// be careful when using flat arrays
	char* my_arr = new char[len];

	copy(my_str.begin(), my_str.end(), my_arr);

	URLify_arr(my_arr, len);

	cout << "URLify_arr: " << my_arr << endl;

	delete[] my_arr;

	return 0;
}
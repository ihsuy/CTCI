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
XML Encoding: Since XML is very verbose, you are given a way of encoding it where each tag gets 
mapped to a pre-defined integer value. The language/grammar is as follows:
*/

string XMLencoding(const string& file_addr, const unordered_map<string, string>& preDefinedKeys)
{
	ifstream inputFile(file_addr);
	if(!inputFile)
	{
		throw runtime_error("Can't open " + file_addr);
	}

	// wash input file
	vector<string> lines;
	string line;
	while(getline(inputFile, line))
	{
		for(int i = 0; i < line.length(); ++i)
		{	
			switch(line[i])
			{
				case '<':
				{
					line.insert(line.begin()+i, ' ');

					i++; // increment i since line is shifted to right by 1

					if(line[i+1] != '/') // assume input file in good format so '<' doesn't exist at the last char
					{	// its a normal start tag
						line.insert(line.begin()+i+1, ' ');
					}	
					else
					{	// its an End tag
						line.insert(line.begin()+i+2, ' ');
					}
					break;
				}
				case '>':
				{	// insert space around the end of bracket
					line.insert(line.begin()+i, ' ');
					i++; // increment i since line is shifted to right by 1
					line.insert(line.begin()+i+1, ' ');
					break;
				}
				case '=': case '\"':
				{	// characters to ignore
					line.replace(i, 1, " ");
					break;
				}
				default:
					break;
			}
		}
		//cout << "line: " << line << endl;
		lines.push_back(line);
	}

	string result;

	for(int i = 0; i < lines.size(); ++i)
	{	// translate
		stringstream ss(lines[i]);
		string token;
		while(ss >> token)
		{	
			if(token == "</")
			{	// its a End tag, ignore until '>' is found
				while(token != ">")
				{
					ss >> token;
				}
			}

			if(token == ">")
			{	// End tag encoded to '0'
				result += "0 ";
				continue;
			}

			if(preDefinedKeys.count(token) != 0)
			{	// this is a predefined tag name
				// encode it
				result += preDefinedKeys.at(token) + " "; 
			}
			else if(token != "<")
			{	// if none of above was true, insert token to result as it is
				result += token + " ";
			}
		}
	}

	return result;
}

int main()
{
	const string addr = "/Users/username/CtCi/chapter16_Moderate/xmlEncoding_inputFile.xml";

	unordered_map<string, string> preDefinedKeys
	{
		{"family", "1"},
		{"person", "2"},
		{"firstName", "3"},
		{"lastName", "4"},
		{"state", "5"}
	};

	cout << XMLencoding(addr, preDefinedKeys) << endl;

	return 0;
}

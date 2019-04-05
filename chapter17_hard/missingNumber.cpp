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
Missing Number: An array A contains all the integers from 0 to n, 
except for one number which is missing. In this problem, we cannot 
access an entire integer in A with a single operation. The elements of 
A are represented in binary, and the only operation we can use to access 
them is "fetch the j th bit of A[i]", which takes constant time. 
design an O(n) time algorithm to find the missing number
*/

// implement the api described in the problem
bool getBit(const vector<int>& A, const int& i, const int& j)
{	// get the j-th bit of A[i]
	return ((A[i]&(1<<j))!=0);
}

vector<int> arrayContainsAllExcept(const int& exp, const int& size)
{
	if(exp >= size)
	{
		throw runtime_error("arrayContainsAllExcept: invalid arguments");
	}

	vector<int> A;
	A.reserve(size);

	for(int i = 0; i < size; ++i)
	{
		if(i != exp)
		{
			A.push_back(i);
		}
	}

	return A;
}

// Solution

vector<int> bitSum(int n)
{	// calculate correct sum of each bit respectively from 0-n
	vector<int> result(32, 0);

	for(int mod = 2, count = 0, block = n/mod; block != 0; count++)
	{	// pattern can be found after careful observation
		int remainder = n%mod;

		int multiplier = (mod>>1);

		block = n/mod;

		int surplus = (multiplier < remainder)?(remainder%multiplier):0;

		result[result.size()-count-1] = multiplier*block+surplus;

		mod <<= 1;
	}

	return result;
}

int findMissingNumber(const vector<int>& A)
{
	vector<int> counter(32, 0); // assume 32 bit integer

	// cout << "counting bits...\n";
	// this is the heavy part 32*n
	for(int i = 0; i < A.size(); ++i)
	{
		for(int b = 0; b < 32; ++b)
		{
			if(getBit(A, i, b))
			{
				counter[31-b]++;
			}
		}
	}

	//cout << "calculating complete bit count...\n";
	vector<int> completeCount = bitSum(A.size()+1);

	int result = 0;

	for(int i = 31, mask = 1; i >= 0; --i, mask <<= 1)
	{	
		//cout << "diff: " << (completeCount[i] - counter[i]) << endl;
		if(completeCount[i] - counter[i] == 1)
		{
			result |= mask;
		}
	}

	return result;
}

int main()
{
	int array_size = 3912300;
	int missing = 892176;
	vector<int> test_vector = arrayContainsAllExcept(missing, array_size);
	cout << "answer : " << missing << '\n';
	cout << "result : " << findMissingNumber(test_vector) << '\n';

	return 0;
}

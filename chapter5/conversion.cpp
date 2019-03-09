#include <iostream>

using namespace std;

int bitFlipsDistance(const int& n1, const int& n2)
{
	int count = 0;
	for(int n = n1^n2; n != 0; n &= (n-1))
	{
		count++;
	}
	return count;
}

int main()
{
	const int n1 = 29;
	const int n2 = 15;

	cout << bitFlipsDistance(n1, n2) << endl;
	return 0;
}


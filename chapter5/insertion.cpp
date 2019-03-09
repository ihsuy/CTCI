#include<iostream>
#include<bitset>

using namespace std;

string itobit(const int& i)
{
	bitset<32> bs(i);
	return bs.to_string();
}

int insertion(const int& M, const int& N, const int& i, const int& j)
{
	int mask1 = ((-1 << (j+1)) | ((1 << i)-1));
	int mask2 = (M << i);

	return (N & mask1) | mask2;
}

int main()
{
	int n1 = -1;
	int n2 = bitset<32>(string("10101010")).to_ulong();
	cout << "n1: " << itobit(n1) << endl;
	cout << "n2: " << itobit(n2) << endl;
	cout << "n3: " << itobit(insertion(n2, n1, 15, 22))<< endl;
 	return 0;
}
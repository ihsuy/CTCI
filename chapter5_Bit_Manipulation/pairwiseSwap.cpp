#include <iostream>
#include <bitset>
using namespace std;

void pairwiseSwap(int& num)
{
	long odd_mask =  bitset<32>("01010101010101010101010101010101").to_ulong();
	long even_mask = bitset<32>("10101010101010101010101010101010").to_ulong();
 	
	num = ((num&odd_mask)<<1) | ((num&(even_mask))>>1);
}

int main()
{
	int i = 123094;
	cout << bitset<32>(i).to_string() << endl;
	pairwiseSwap(i);
	cout << bitset<32>(i).to_string() << endl;
	return 0;
}
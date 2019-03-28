#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <bitset>

using namespace std;

struct testingStrip
{
	bool isPositive;

	int days_elapsed;

	testingStrip(): isPositive(false), days_elapsed(0){}

	void test_with(const bool& soda_is_posionous);
	bool get_result();
	void waitForOneDay();
};

void testingStrip::test_with(const bool& soda_is_posionous)
{
	if(soda_is_posionous)
	{
		isPositive = true;
	}
}

bool testingStrip::get_result()
{
	if(days_elapsed < 7)
	{
		throw runtime_error("Please wait! Result will be out in "+ to_string(7-days_elapsed) + " days!"); 
	}
	else
	{
		return isPositive;
	}
}

void testingStrip::waitForOneDay()
{
	days_elapsed++;
}

vector<bool> fillSodaBottles(const int& nBottle)
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	vector<bool> bottles(nBottle, false);

	int poison_index = rand()%nBottle;

	bottles[poison_index] = true;

	return bottles;
}

void FindOutPosionBottle(const vector<bool>& bottles, vector<testingStrip>& strips)
{
	// add soda from i-th bottle to strips 
	// with repect to i's binary representation

	cout << "Adding soda drops to testing strips..." << endl;

	for(int i = 0; i < bottles.size(); ++i)
	{
		string bstr = bitset<10>(i+1).to_string();
		for(int j = 0; j < strips.size(); ++j)
		{
			if(bstr[j] == '1')
			{
				strips[j].test_with(bottles[i]);
			}
		}
	}

	// wait 7 days 
	int days_left = 7;

	cout << "Waiting for " << days_left << " days..."<< endl;

	while(days_left--)
	{
		for(auto& strip : strips)
		{
			strip.waitForOneDay();
		}
	}

	// get the result
	cout << "Result is out!\nAfter experiment, the strips look like:" << endl;
	for(int i = 0; i < strips.size(); ++i)
	{
		cout << "TestingStrip #" << i+1 << ((strips[i].get_result())?"  Postive" : "  Negative") << endl;  
	}

	// consider the result as the binary representation of the target bottle index
	// convert that index to decimal

	string bstr2;
	bstr2.reserve(strips.size());

	for(auto strip : strips)
	{
		bstr2 += ((strip.get_result())?'1':'0');
	}

	cout << "Experiment result : Posion is in the " << bitset<10>(bstr2).to_ulong()
	     << "th bottle" << endl;

	int ans = 0;
	for(;ans < bottles.size();++ans)
	{
		if(bottles[ans] == 1)
		{
			break;
		}
	}

	cout << "Answer: " << ans+1 << endl;
}

int main()
try{
	const int nBottle = 1000;
	const int nStrip = 10;

	vector<bool> bottles = fillSodaBottles(nBottle);

	vector<testingStrip> strips(nStrip, testingStrip());

	FindOutPosionBottle(bottles, strips);


	return 0;
}
catch(runtime_error& re)
{
	cout << re.what() << endl;
}
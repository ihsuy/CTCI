#include <iostream>
#include <stack>
#include <vector>

using namespace std;



struct hanoiTower
{
	static int towerCount;

	stack<int> tower;

	int towerName;

	hanoiTower(const int& nd): towerName(towerCount + 1)
	{
		if (towerCount != 0)
		{
			throw runtime_error("Can't create more than one hanoiTower with disks");
		}
		else
		{
			towerCount++;
			for (int i = nd; i > 0; --i)
			{
				tower.push(i);
			}
		}

	}

	hanoiTower(): towerName(towerCount + 1)
	{
		towerCount++;
		if (towerCount > 3)
		{
			throw runtime_error("Can't create more than 3 hanoiTowers");
		}
	}

	bool addDisk(const int& disk)
	{
		if (tower.size() == 0 or tower.top() > disk)
		{
			tower.push(disk);
			return true;
		}
		else
		{
			cout << "Trying to add " << disk << " to tower#" << towerName << " top: " << tower.top() << "\nfail to add a smaller disk on top of a bigger disk\n";
			return false;
		}
	}

	int getTopDisk()
	{
		if(tower.size() == 0)
		{
			cout << "Trying to get disk from tower#" << towerName << " size " << 0 << "\nfail to get disk from an empty tower\n";
			return -1;
		}

		int topDisk = tower.top();
		tower.pop();
		return topDisk;
	}

};

struct towersOfHanoi
{
	const int n_disks;

	hanoiTower t1;
	hanoiTower t2;
	hanoiTower t3;

	towersOfHanoi(const int& n): n_disks(n), t1(n), t2{}, t3{} {}

	int size() const
	{
		return n_disks;
	}

	void shift(const int& i1, const int& i2)
	{
		hanoiTower* tmp1 = &t1, *tmp2 = &t2;
		if(i1 == 2)
		{
			tmp1 = &t2;
		}
		else if(i1 == 3)
		{
			tmp1 = &t3;
		}

		if(i2 == 1)
		{
			tmp2 = &t1;
		}
		else if(i2 == 3)
		{
			tmp2 = &t3;
		}

		tmp2->addDisk(tmp1->getTopDisk());
	}

	void visualize()
	{
		stack<int> s1 = t1.tower;
		stack<int> s2 = t2.tower;
		stack<int> s3 = t3.tower;
		vector<int> buffer;
		cout << "===========\n";

		cout << '|';
		while(s1.size()!=0)
		{
			buffer.insert(buffer.begin(), s1.top());
			s1.pop();
		}
		for(int i = 0; i < buffer.size(); ++i)
		{
			cout << buffer[i] << '-';
		}
		cout << '\n';

		buffer = vector<int>();
		cout << '|';
		while(s2.size()!=0)
		{
			buffer.insert(buffer.begin(), s2.top());
			s2.pop();
		}
		for(int i = 0; i < buffer.size(); ++i)
		{
			cout << buffer[i] << '-';
		}
		cout << '\n';

		buffer = vector<int>();
		cout << '|';
		while(s3.size()!=0)
		{
			buffer.insert(buffer.begin(), s3.top());
			s3.pop();
		}
		for(int i = 0; i < buffer.size(); ++i)
		{
			cout << buffer[i] << '-';
		}
		cout << '\n';
	}

};

int hanoiTower::towerCount = 0;

void hanoiSolver(towersOfHanoi& toh)
{
	if(toh)
}

int main()
try {

	towersOfHanoi toh(3);

	toh.visualize();

	toh.shift(1, 3);

	toh.visualize();

	toh.shift(1, 2);

	toh.visualize();

	toh.shift(3, 2);

	toh.visualize();

	toh.shift(1, 3);

	toh.visualize();

	toh.shift(2, 1);

	toh.visualize();

	toh.shift(2, 3);

	toh.visualize();

	toh.shift(1, 3);

	toh.visualize();
	return 0;
}
catch (runtime_error& er)
{
	cout << er.what() << endl;
}
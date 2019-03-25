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

using namespace std;

/*
Timing tool for measuring how long time the sort algorithm takes to sort an array
*/

void timeIt(void (*sortAlgorithm)(vector<int>&), const string& name, vector<int>& v)
{
	cout << "<<<<<<<<timeIt<<<<<<<<\n";
	int N = v.size();
	cout << "Sorting " << N << " integers...\n";

	auto t1 = chrono::high_resolution_clock::now();
	sortAlgorithm(v);
	auto t2 = chrono::high_resolution_clock::now() - t1;

	auto time_in_nano = chrono::duration_cast<chrono::nanoseconds>(t2).count();
	auto time_in_micro = chrono::duration_cast<chrono::microseconds>(t2).count();

	cout << "Completed\n";
	cout << "Sorted " << N << " integers using " << name << '\n';
	cout << "Time elapsed:\n" << time_in_micro/1000 << " milliseconds\n";
	cout << time_in_micro << " microseconds\n";
	cout << time_in_nano << " nanoseconds\n";
}


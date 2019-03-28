#include <iostream>
#include <vector>
using namespace std;


long long tripleSteps_helper(const int& firstStep, const int& nStairs, vector<vector<long long>>& cache)
{

	if (firstStep > nStairs)
	{
		return 0;
	}

	if (firstStep == nStairs)
	{
		return 1;
	}

	int stairsLeft = nStairs - firstStep;

	long long result = 0;

	if (cache[firstStep-1][nStairs-1] == -1)
	{
		long long n1 = tripleSteps_helper(1, stairsLeft, cache);
		long long n2 = tripleSteps_helper(2, stairsLeft, cache);
		long long n3 = tripleSteps_helper(3, stairsLeft, cache);

		result = n1 + n2 + n3;
		cache[firstStep-1][nStairs-1] = result;
	}
	else
	{
		result = cache[firstStep-1][nStairs-1];
	}	

	return result;

}

long long tripleSteps(const int& nStairs)
{
	vector<vector<long long>> cache(3, vector<long long>(nStairs, -1));

	return tripleSteps_helper(1, nStairs, cache)
	       + tripleSteps_helper(2, nStairs, cache)
	       + tripleSteps_helper(3, nStairs, cache);
}

int main()
{
	const int nStairs = 5;

	cout << tripleSteps(nStairs) << endl;
	return 0;
}
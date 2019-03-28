#include <iostream>
#include <map>
#include <chrono>
#include <array>
#include <algorithm>
using namespace std;

constexpr static int upb = 40;

long long fibonacci_handler(const int& n, long long (&cache)[upb+1])
{	// calculate n-th fibonacci number
	if (n <= 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}

	long long result;

	if (cache[n] == 0)
	{
		result = fibonacci_handler(n - 1, cache) + fibonacci_handler(n - 2, cache);

		cache[n] = result;
	}
	else
	{
		result = cache[n];
	}

	return result;
}

long long fibonacci(const int& n)
{

	long long cache[upb+1];

	fill(cache, cache+upb+1, 0);

	return fibonacci_handler(n, cache);
}

long long fibonacci_bruteForce(const int& n)
{
	if (n <= 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}

	return fibonacci_bruteForce(n-1) + fibonacci_bruteForce(n-2);
}

long long fibonacci_iterative(const int& n)
{
	int a = 0, b = 1, c = 0;
	if(n == 0)
	{
		return 0;
	}
	else if(n == 1)
	{
		return 1;
	}

	for(int i = 0; i < n-1qqq ; ++i)
	{
		c = a+b;
		a = b;
		b = c;
	}

	return c;
}

int main()
{

	auto t1 = chrono::high_resolution_clock::now();
	for (int i = 1; i <= upb; ++i)
	{
		cout << fibonacci(i) << '\n';
	}
	auto t2 = chrono::high_resolution_clock::now() - t1;
	auto time1 = (double)chrono::duration_cast<chrono::microseconds>(t2).count()/1e6;
	cout << "computing first " << upb << " fibonacci numbers with memory\n";
	cout << "time elapsed: " << time1 << " sec\n";

	t1 = chrono::high_resolution_clock::now();
	for (int i = 1; i <= upb; ++i)
	{
		cout << fibonacci_bruteForce(i) << endl;
	}
	t2 = chrono::high_resolution_clock::now() - t1;
	auto time2 = (double)chrono::duration_cast<chrono::microseconds>(t2).count()/1e6;
	cout << "computing first " << upb << " fibonacci numbers WIHTOUT memory\n";
	cout << "time elapsed: " << time2 << " sec\n";

	cout << "using memory increased time performance by: x" << time2/time1 << '\n';


	t1 = chrono::high_resolution_clock::now();
	for (int i = 1; i <= upb; ++i)
	{
		cout << fibonacci_iterative(i) << endl;
	}
	t2 = chrono::high_resolution_clock::now() - t1;
	auto time3 = (double)chrono::duration_cast<chrono::microseconds>(t2).count()/1e6;

		cout << "using memory increased time performance by: x" << time2/time3 << '\n';

	return 0;
}
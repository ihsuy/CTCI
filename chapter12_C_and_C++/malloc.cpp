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

typedef long long ll;
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*

Malloc: Write an aligned malloc and free function that
supports allocating memory such that the memory address
returned is divisible by a specific power of two.
*/

void* aligned_malloc(const int& n/*memory size*/, const int& m/*return address divible by 2^m*/)
{
	long long divisor = 1 << m;

	void* mblock = malloc(divisor + n - 1 + sizeof(void*));

	void* addr =(void*)((size_t)mblock - ((size_t)mblock % divisor) + divisor);

	// secretly store mblock's original position 1 before addr
	// use it later as the handler to delete this whole chunk of memory
	((void**)addr)[-1] = mblock;

	return addr;
}

void aligned_free(void* p)
{
	free(((void**)p)[-1]);
}

int main()
{
	void* m = aligned_malloc(100, 7);

	cout << (size_t)m << endl;

	aligned_free(m);

	return 0;
}

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
Stack of Boxes: You have a stack of n boxes, with widths Wi' heights hi'
and depths di.The boxes cannot be rotated and can only be stacked on top
of one another if each box in the stack is strictly larger than the box
above it in width, height, and depth. Implement a method to compute the
height of the tallest possible stack.The height of a stack is the sum of
the heights of each box.
*/

struct box
{
	int w, h, d;
	box(const int& width, const int& height, const int& depth)
		: w(width), h(height), d(depth) {}

	bool operator>(const box& b2) const
	{
		return (w > b2.w and h > b2.h and d > b2.d);
	}
};

int stackOfBoxes_helper(const vector<box>& boxes, const int& top,
                        unordered_map<int, unordered_map<int, int>>& buffer)
{
	if (boxes.size() == 0)
	{
		return 0;
	}

	int result = boxes[top].h;
	int next_h = 0;

	for (int i = top+1; i < boxes.size(); ++i)
	{
		if (boxes[i] > boxes[top])
		{
			int temp_h;

			if (buffer.find(top) != buffer.end() and buffer[top].find(i) != buffer[top].end())
			{
				temp_h = buffer[top][i];
			}
			else
			{
				temp_h = stackOfBoxes_helper(boxes, i, buffer);
				buffer[top][i] = temp_h;
			}

			if (temp_h > next_h)
			{
				next_h = temp_h;
			}
		}
	}
	return result + next_h;
}

int stackOfBoxes(vector<box>& boxes)
{
	unordered_map<int, unordered_map<int, int>> buffer;
	//int max_h = 0;

	sort(boxes.begin(), boxes.end(), [](const box & b1, const box & b2) {
		return b1.h < b2.h;
	});

	int result = 0;
	for(int i = 0; i < boxes.size(); ++i)
	{
		int temp = stackOfBoxes_helper(boxes, i, buffer);
		if(temp > result)
		{
			result = temp;
		}
	}
	return result;
}

int main()
{
	vector<box> boxes
	{
		box(3, 5, 3),
		box(8, 8, 4),
		box(2, 2, 2),
		box(1, 1, 1),
		box(10, 9, 10),
	};

	cout << stackOfBoxes(boxes) << '\n';

	return 0;
}


/*		auto removedBox = *(boxes.begin()+top);
		cout << "removed: " << removedBox.w << " " << removedBox.h << " " << removedBox.d << '\n';
		boxes.erase(boxes.begin()+top);
		cout << "box: ";
		for(auto& item: boxes)
		{
			cout << item.w << " " << item.h << " " << item.d << ", ";
		}
		cout << '\n';*/
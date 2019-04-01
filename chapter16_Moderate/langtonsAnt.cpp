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
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <iomanip>

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
Langton'sAnt:Anantissittingonaninfinitegridofwhiteandblacksquares.Itinitiallyfacesright.
At each step, it does the following:
(1) At a white square, flip the color of the square, turn 90 degrees right (clockwise),
 and move forward one unit.
(2) At a black square, flip the color of the square, turn 90 degrees left (counter-clockwise).
 and move forward one unit.
Write a program to simulate the first K moves that the ant makes and print the final
board as a grid. Note that you are not provided with the data structure to represent
the grid. This is something you must design yourself. The only input to your method is K.
You should print the final grid and return nothing.Themethodsignaturemightbesomethinglikevoid
 printKMoves(int K).
*/

enum marker
{
	BLACK_SQUARE = '#', WHITE_SQUARE = ' '
};

enum directions
{
	UP = 0, RIGHT, DOWN, LEFT
};

vector<string> createGrid(const int& width, const int& height)
{
	return vector<string>(height, string(width, WHITE_SQUARE));
}

void displayGrid(const vector<string>& grid)
{
	for (int i = 0; i < grid.size(); ++i)
	{
		cout << grid[i] << '\n';
	}
}

void turnClockwise(directions& dir)
{
	dir = (directions)(((int)dir + 1) % 4);
}
void turnCounterClockwise(directions& dir)
{
	dir = (directions)(((int)dir + 3) % 4);
}

void moveAlone(const directions& dir, int& cur_r, int& cur_c)
{
	switch (dir)
	{
	case UP:
		cur_r--;
		break;
	case RIGHT:
		cur_c++;
		break;
	case DOWN:
		cur_r++;
		break;
	case LEFT:
		cur_c--;
		break;
	}
}

void ant_progress(vector<string>& grid, int& cur_r, int& cur_c, directions& dir)
{
	if (grid[cur_r][cur_c] == WHITE_SQUARE)
	{
		grid[cur_r][cur_c] = BLACK_SQUARE; // flip color
		turnClockwise(dir);
		moveAlone(dir, cur_r, cur_c);
	}
	else
	{
		grid[cur_r][cur_c] = WHITE_SQUARE;
		turnCounterClockwise(dir);
		moveAlone(dir, cur_r, cur_c);
	}
}

void langtonsAntSimulator(const int& width, const int& height, const int& speed = 1)
{	// set default initial position to middle of the grid

	vector<string> grid = createGrid(width, height);

	chrono::milliseconds pause_t = chrono::milliseconds(100 / speed);

	int ant_r = (height / 2)-5, ant_c = width / 2;

	directions ant_dir = RIGHT;

	while (ant_r >= 0 and ant_r < height and ant_c >= 0 and ant_c < width)
	{
		displayGrid(grid);

		ant_progress(grid, ant_r, ant_c, ant_dir);

		this_thread::sleep_for(pause_t);

		system("clear");
	}
}

int main()
{
	const int width = 80;
	const int height = 30;
	const int speed = 3;

	langtonsAntSimulator(width, height, speed);

	return 0;
}


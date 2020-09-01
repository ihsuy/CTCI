#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

enum MOVE { RIGHT, DOWN, NULL_MOVE };

enum gridMark { EMPTY, OBSTACLE, BEEN_HERE };

void deployObstacle(vector<vector<gridMark>>& grid,
                    const vector<pair<int, int>>& loc) {
    for (int i = 0; i < loc.size(); ++i) {
        grid[loc[i].second][loc[i].first] = OBSTACLE;
    }
}

void showGrid(const vector<vector<gridMark>>& grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == gridMark::EMPTY) {
                cout << '=';
            } else if (grid[i][j] == gridMark::OBSTACLE) {
                cout << 'O';
            } else if (grid[i][j] == gridMark::BEEN_HERE) {
                cout << '.';
            } else if (grid[i][j] == gridMark::BEEN_HERE) {
                cout << '.';
            } else {
                cout << '?';
            }
        }
        cout << '\n';
    }
}

vector<MOVE> findRoute(vector<vector<gridMark>>& grid) {  // iterative
    vector<MOVE> route;

    int x = 0, y = 0;

    int target_x = grid[0].size() - 1;
    int target_y = grid.size() - 1;

    stack<pair<pair<int, int>, MOVE>> crossRoads;

    while (x != target_x or y != target_y) {
        if ((x != grid[0].size() - 1 and y != grid.size() - 1) and
            grid[y][x + 1] == 1 and grid[y + 1][x] != 1) {
            // paint route on grid
            grid[y][x] = gridMark::BEEN_HERE;

            route.push_back(MOVE::DOWN);
            y++;
        } else if ((x != grid[0].size() - 1 and y != grid.size() - 1) and
                   grid[y][x + 1] != 1 and grid[y + 1][x] == 1) {
            grid[y][x] = gridMark::BEEN_HERE;

            route.push_back(MOVE::RIGHT);
            x++;
        } else if (grid[y][x] == gridMark::EMPTY and
                   (x != grid[0].size() - 1 and y != grid.size() - 1) and
                   grid[y][x + 1] != 1 and grid[y + 1][x] != 1) {
            int x_dist = target_x - x;
            int y_dist = target_y - y;

            if (x_dist > y_dist) {
                crossRoads.push(make_pair(make_pair(x, y), RIGHT));

                grid[y][x] = gridMark::BEEN_HERE;

                route.push_back(MOVE::RIGHT);
                x++;
            } else {
                crossRoads.push(make_pair(make_pair(x, y), DOWN));

                grid[y][x] = gridMark::BEEN_HERE;

                route.push_back(MOVE::DOWN);
                y++;
            }
        } else if (x == grid[0].size() - 1 or y == grid.size() - 1) {
            if (x == grid[0].size() - 1) {
                // godown
                grid[y][x] = gridMark::BEEN_HERE;

                route.push_back(MOVE::DOWN);
                y++;
            } else {
                grid[y][x] = gridMark::BEEN_HERE;

                route.push_back(MOVE::RIGHT);
                x++;
            }
        } else {
            if (crossRoads.size() != 0) {
                x = crossRoads.top().first.first;
                y = crossRoads.top().first.second;

                if (crossRoads.top().second == MOVE::RIGHT) {
                    grid[y][x] = gridMark::BEEN_HERE;
                    route.push_back(MOVE::DOWN);

                    y++;
                } else {
                    grid[y][x] = gridMark::BEEN_HERE;
                    route.push_back(MOVE::RIGHT);

                    x++;
                }

                crossRoads.pop();
            } else {
                return vector<MOVE>();
            }
        }
    }
    return route;
}

bool findRoute_helper(vector<vector<gridMark>>& grid,
                      const int& r,
                      const int& c,
                      vector<vector<gridMark>>& path,
                      vector<vector<int>>& cache) {
    if (r < 0 or c < 0 or grid[r][c] == gridMark::OBSTACLE) {
        return false;
    }

    if (cache[r][c] == 1) {
        return true;
    } else if (cache[r][c] == 2) {
        return false;
    }

    bool atStartingPoint = ((r == 0) and (c == 0));

    if (atStartingPoint or findRoute_helper(grid, r - 1, c, path, cache) or
        findRoute_helper(grid, r, c - 1, path, cache)) {
        path[r][c] = gridMark::BEEN_HERE;
        cache[r][c] = 1;
        return true;
    }

    cache[r][c] = 2;

    return false;
}

vector<vector<gridMark>> findRoute_recursive(vector<vector<gridMark>>& grid) {
    vector<vector<int>> cache(grid.size(), vector<int>(grid[0].size(), 0));

    vector<vector<gridMark>> path(
        grid.size(), vector<gridMark>(grid[0].size(), gridMark::EMPTY));

    findRoute_helper(grid, grid.size() - 1, grid[0].size() - 1, path, cache);

    return path;
}

void createObstacle(const int& r,
                    const int& c,
                    const int& n,
                    vector<pair<int, int>>& obstacles) {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; ++i) {
        obstacles.push_back(make_pair(rand() % c, rand() % r));
    }
}

int main() {
    const int r = 800;
    const int c = 80;

    vector<vector<gridMark>> grid(r, vector<gridMark>(c, gridMark::EMPTY));

    vector<pair<int, int>> obstacles;

    createObstacle(r, c, 5500, obstacles);

    deployObstacle(grid, obstacles);

    // vector<vector<gridMark>> gridcp = grid;

    // showGrid(grid);

    // auto rou = findRoute(grid);
    // if (rou.size() == 0)
    // {
    // 	cout << "didn't find route\n";
    // }
    // else
    // {
    // 	for (int i = 0; i < rou.size(); ++i)
    // 	{
    // 		cout << ((rou[i] == MOVE::RIGHT) ? "RIGHT " : "DOWN ");
    // 	}
    // }
    cout << '\n';

    auto cac = findRoute_recursive(grid);

    for (int i = 0; i < cac.size(); ++i) {
        for (int j = 0; j < cac[0].size(); ++j) {
            if (grid[i][j] == gridMark::OBSTACLE) {
                cout << '\'';
            } else if (cac[i][j] == gridMark::BEEN_HERE) {
                cout << '+';
            } else {
                cout << ' ';
            }
        }
        cout << '\n';
    }

    // cout << "OVER" << endl;

    // findRoute(gridcp);

    // for(int i = 0; i < gridcp.size(); ++i)
    // {
    // 	for(int j = 0; j < gridcp[0].size(); ++j)
    // 	{
    // 		if(gridcp[i][j] == gridMark::OBSTACLE)
    // 		{
    // 			cout << '\'';
    // 		}
    // 		else if (gridcp[i][j] == gridMark::BEEN_HERE)
    // 		{
    // 			cout << '+';
    // 		}
    // 		else
    // 		{
    // 			cout << ' ';
    // 		}
    // 	}
    // 	cout << '\n';
    // }

    return 0;
}
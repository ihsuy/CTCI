/*
Zero Matrix: Write an algorithm such that if an
element in an MxN matrix is 0, its entrie row and
column are set to 0
*/

#include <iostream>
#include <vector>

using namespace std;

void showMatrix(const vector<vector<int>> m) {
    cout << "===" << endl;
    for (auto row : m) {
        cout << "| ";
        for (auto item : row) {
            cout << item << " ";
        }
        cout << '|' << endl;
    }
    cout << "===" << endl;
}

void colrow_marker(vector<vector<int>>& m,
                   const int& row,
                   const int& col,
                   const int& mark) {
    for (int i = 0; i < m.size(); ++i) {
        if (m[i][col] != mark and m[i][col] != 0) {
            m[i][col] = mark;
        }
    }
    for (int i = 0; i < m[0].size(); ++i) {
        if (m[row][i] != mark and m[row][i] != 0) {
            m[row][i] = mark;
        }
    }
}

void Zeronize(vector<vector<int>>& m) {
    int minval = INT_MAX;
    for (auto row : m) {
        for (auto key : row) {
            if (key < minval) {
                minval = key;
            }
        }
    }
    int mark = minval - 1;
    int tar;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            tar = m[i][j];
            if (tar == mark) {
                continue;
            }
            if (tar == 0) {
                colrow_marker(m, i, j, mark);
            }
        }
    }

    for (auto& row : m) {
        for (auto& key : row) {
            if (key == mark) {
                key = 0;
            }
        }
    }
}

int main() {
    vector<vector<int>> m = {
        {1, 2, 4, 8, 1}, {1, 0, 2, 1, 0}, {1, 0, 2, 2, 1}, {1, 1, 1, 1, 1}};
    Zeronize(m);
    showMatrix(m);
    return 0;
}
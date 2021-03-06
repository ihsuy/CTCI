/*
Given an image represented by an NxN matrix, where
each pixel in the image is 4 bytes, write a method
to rotate the image by 90 degrees. (do this in-place)
*/

#include <iostream>
#include <vector>

using namespace std;

/*
for a matrix A NxN, the n-layer is defined as:
all entries that are surrouding the (N-1-n)x(N-1-n) submatrix at center of A
*/

// does in place rotation of layers
void layerRotate(vector<vector<int>>& m,
                 const int& n,
                 const bool& clockwise = true) {
    int w = m.size() - 1 - n;

    for (int i = n; i < w; ++i) {
        int u_col = i, u_row = n, r_col = w, r_row = i, d_col = w + n - i,
            d_row = w, l_col = n, l_row = w + n - i;

        if (clockwise) {
            int temp = m[u_row][u_col];
            m[u_row][u_col] = m[l_row][l_col];
            m[l_row][l_col] = m[d_row][d_col];
            m[d_row][d_col] = m[r_row][r_col];
            m[r_row][r_col] = temp;
        } else {
            int temp = m[u_row][u_col];
            m[u_row][u_col] = m[r_row][r_col];
            m[r_row][r_col] = m[d_row][d_col];
            m[d_row][d_col] = m[l_row][l_col];
            m[l_row][l_col] = temp;
        }
    }
}

// loops over the "layers" and rotate each of them
void matrixRotate(
    vector<vector<int>>& m,
    const bool& clockwise = true) {  // input verification is omitted

    for (int i = 0; i < m.size() / 2; ++i) {
        layerRotate(m, i, clockwise);
    }
}

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

int main() {
    vector<vector<int>> m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    showMatrix(m);
    matrixRotate(m);
    showMatrix(m);
    matrixRotate(m);
    matrixRotate(m);
    showMatrix(m);

    return 0;
}

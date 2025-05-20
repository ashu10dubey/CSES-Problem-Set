#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            set<int> used;

            // check left in the same row
            for (int k = 0; k < j; k++) {
                used.insert(grid[i][k]);
            }

            // check above in the same column
            for (int k = 0; k < i; k++) {
                used.insert(grid[k][j]);
            }

            // find smallest nonnegative integer not used
            int val = 0;
            while (used.count(val)) val++;

            grid[i][j] = val;
        }
    }

    // Output the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << (j + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}

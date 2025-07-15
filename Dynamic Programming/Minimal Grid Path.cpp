#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<pair<int, int>> curr = {{0, 0}};
    string result = string(1, grid[0][0]);

    visited[0][0] = true;

    for (int step = 0; step < 2 * n - 2; ++step) {
        char minChar = 'Z' + 1;
        vector<pair<int, int>> next;

        // Find minimum character available at next positions
        for (auto [x, y] : curr) {
            if (x + 1 < n) minChar = min(minChar, grid[x + 1][y]);
            if (y + 1 < n) minChar = min(minChar, grid[x][y + 1]);
        }

        for (auto [x, y] : curr) {
            if (x + 1 < n && grid[x + 1][y] == minChar && !visited[x + 1][y]) {
                visited[x + 1][y] = true;
                next.emplace_back(x + 1, y);
            }
            if (y + 1 < n && grid[x][y + 1] == minChar && !visited[x][y + 1]) {
                visited[x][y + 1] = true;
                next.emplace_back(x, y + 1);
            }
        }

        result += minChar;
        curr = move(next);
    }

    cout << result << "\n";
    return 0;
}

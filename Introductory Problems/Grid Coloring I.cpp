#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    char chars[] = {'A', 'B', 'C', 'D'};
    vector<string> result = grid;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char c : chars) {
                if (c != grid[i][j]) {
                    bool valid = true;
                    if (i > 0 && result[i-1][j] == c) valid = false;
                    if (j > 0 && result[i][j-1] == c) valid = false;
                    if (valid) {
                        result[i][j] = c;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << result[i] << "\n";
    }
    return 0;
}

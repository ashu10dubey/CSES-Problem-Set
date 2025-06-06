#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Time Complexity: O(n + m)
// Space Complexity: O(n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 1);       // 1-based indexing
    vector<int> pos(n + 1);       // pos[value] = index in arr

    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }

    int rounds = 1;
    for (int i = 2; i <= n; ++i) {
        if (pos[i] < pos[i - 1]) {
            ++rounds;
        }
    }

    while (m--) {
        int a, b;
        cin >> a >> b;

        int va = arr[a], vb = arr[b];

        // Set to store affected pairs
        vector<pair<int, int>> affected;

        for (int d = -1; d <= 1; ++d) {
            int x = va + d;
            if (1 <= x && x <= n) {
                affected.emplace_back(x - 1, x);
            }
            x = vb + d;
            if (1 <= x && x <= n) {
                affected.emplace_back(x - 1, x);
            }
        }

        // Remove duplicate pairs
        sort(affected.begin(), affected.end());
        affected.erase(unique(affected.begin(), affected.end()), affected.end());

        // Subtract rounds for affected pairs before swap
        for (auto [x, y] : affected) {
            if (x >= 1 && y <= n && pos[x] > pos[y]) {
                --rounds;
            }
        }

        // Perform the swap
        swap(arr[a], arr[b]);
        pos[va] = b;
        pos[vb] = a;

        // Add rounds for affected pairs after swap
        for (auto [x, y] : affected) {
            if (x >= 1 && y <= n && pos[x] > pos[y]) {
                ++rounds;
            }
        }

        cout << rounds << '\n';
    }

    return 0;
}

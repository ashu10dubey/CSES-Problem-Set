#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<pair<long long, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1; // Store original index (1-based)
    }

    // Map from sum of two values -> list of pairs of indices
    unordered_map<long long, vector<pair<int, int>>> twoSum;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long current_sum = a[i].first + a[j].first;
            long long remaining = x - current_sum;

            // Check if remaining sum exists in map
            if (twoSum.count(remaining)) {
                for (auto &p : twoSum[remaining]) {
                    int k = p.first;
                    int l = p.second;
                    if (k != i && k != j && l != i && l != j) {
                        // Found 4 distinct indices
                        cout << a[i].second << " " << a[j].second << " " << a[k].second << " " << a[l].second << "\n";
                        return 0;
                    }
                }
            }
        }

        // Add all previous pairs with i to the map (only after checking to avoid using same pair)
        for (int j = 0; j < i; ++j) {
            long long pair_sum = a[i].first + a[j].first;
            twoSum[pair_sum].emplace_back(i, j);
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
} 

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;

    vector<int> a(n);
    for (int &num : a) cin >> num;

    // Store pair sums: sum -> list of index pairs (i, j)
    unordered_map<long long, pair<int, int>> sum_map;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long target = x - (a[i] + a[j]);

            // Check if target sum exists in map
            if (sum_map.count(target)) {
                auto [p1, p2] = sum_map[target];
                if (p1 != i && p1 != j && p2 != i && p2 != j) {
                    // Output 1-based indices
                    cout << p1 + 1 << " " << p2 + 1 << " " << i + 1 << " " << j + 1 << endl;
                    return 0;
                }
            }
        }

        // Add all previous sums with a[i] to the map after checking
        for (int j = 0; j < i; ++j) {
            long long sum = a[i] + a[j];
            sum_map[sum] = {j, i};  // Store last seen pair
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}

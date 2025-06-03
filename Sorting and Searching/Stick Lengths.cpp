#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Time Complexity: O(n log n) — due to sorting
// Space Complexity: O(n) — storing the stick lengths

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> sticks(n);
    for (int i = 0; i < n; ++i) {
        cin >> sticks[i];
    }

    sort(sticks.begin(), sticks.end());

    // Use median as the target length
    long long median = sticks[n / 2];
    long long total_cost = 0;

    for (int i = 0; i < n; ++i) {
        total_cost += abs(sticks[i] - median);
    }

    cout << total_cost << '\n';
    return 0;
}

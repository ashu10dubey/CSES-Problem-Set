#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (int &i : w) cin >> i;

    // dp[mask] = {rides_used, weight_of_last_ride}
    vector<pair<int, int>> dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};  // Empty set: 1 ride with 0 weight

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                int prev = mask ^ (1 << i);
                auto [rides, last_w] = dp[prev];
                if (last_w + w[i] <= x) {
                    dp[mask] = min(dp[mask], {rides, last_w + w[i]});
                } else {
                    dp[mask] = min(dp[mask], {rides + 1, w[i]});
                }
            }
        }
    }

    cout << dp[(1 << n) - 1].first << '\n';
    return 0;
}

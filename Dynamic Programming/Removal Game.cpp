#include <bits/stdc++.h> 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + x[i];
    }

    auto get_sum_range = [&](int i, int j) {
        if (i > j) return 0LL;
        return prefix_sum[j + 1] - prefix_sum[i];
    };

    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;

            if (len == 1) {
                dp[i][j] = x[i];
            } else {
                long long score_if_take_i = x[i] + (get_sum_range(i + 1, j) - dp[i + 1][j]);
                long long score_if_take_j = x[j] + (get_sum_range(i, j - 1) - dp[i][j - 1]);
                dp[i][j] = max(score_if_take_i, score_if_take_j);
            }
        }
    }

    cout << dp[0][n - 1] << endl;

    return 0;
}
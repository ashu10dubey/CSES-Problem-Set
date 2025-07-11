#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (int &v : x) cin >> v;

    vector<vector<int>> dp(n, vector<int>(m + 2, 0));

    // Base case
    if (x[0] == 0) {
        for (int v = 1; v <= m; ++v) dp[0][v] = 1;
    } else {
        dp[0][x[0]] = 1;
    }
    // DP transitions
    for (int i = 1; i < n; ++i) {
        if (x[i] == 0) {
            for (int v = 1; v <= m; ++v) {
                dp[i][v] = ((dp[i - 1][v - 1] + dp[i - 1][v]) % MOD + dp[i - 1][v + 1]) % MOD;
            }
        } else {
            int v = x[i];
            dp[i][v] = ((dp[i - 1][v - 1] + dp[i - 1][v]) % MOD + dp[i - 1][v + 1]) % MOD;
        }
    }
    // Answer is the sum of last row
    int result = 0;
    for (int v = 1; v <= m; ++v) result = (result + dp[n - 1][v]) % MOD;

    cout << result << "\n";
    return 0;
}

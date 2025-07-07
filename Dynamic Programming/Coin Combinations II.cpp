#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for (int &c : coins) cin >> c;

    vector<int> dp(x + 1, 0);
    dp[0] = 1; // base case: one way to make sum 0

    for (int coin : coins) {
        for (int i = coin; i <= x; ++i) {
            dp[i] = (dp[i] + dp[i - coin]) % MOD;
        }
    }

    cout << dp[x] << "\n";
    return 0;
}

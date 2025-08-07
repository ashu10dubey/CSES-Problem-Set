#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> dp(n + 1);
    dp[0] = 1;

    vector<int> last(26, -1); // for 'a' to 'z'

    for (int i = 1; i <= n; ++i) {
        dp[i] = (2LL * dp[i - 1]) % MOD;

        int ch = s[i - 1] - 'a';
        if (last[ch] != -1) {
            dp[i] = (dp[i] - dp[last[ch]] + MOD) % MOD;
        }
        last[ch] = i - 1;
    }

    cout << (dp[n] - 1 + MOD) % MOD << "\n"; // subtract empty subsequence
    return 0;
}

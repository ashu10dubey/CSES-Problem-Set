#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
ll dp[20][11][2][2];  // pos, prev digit, tight, leading_zero

ll count_dp(int pos, int prev, bool tight, bool leading_zero) {
    if (pos == s.size()) return 1;  // base case: valid number

    if (dp[pos][prev][tight][leading_zero] != -1)
        return dp[pos][prev][tight][leading_zero];

    ll res = 0;
    int limit = tight ? (s[pos] - '0') : 9;

    for (int d = 0; d <= limit; ++d) {
        if (!leading_zero && d == prev) continue;  // adjacent check
        res += count_dp(pos + 1, d, tight && (d == limit), leading_zero && d == 0);
    }

    return dp[pos][prev][tight][leading_zero] = res;
}

ll solve(ll x) {
    s = to_string(x);
    memset(dp, -1, sizeof(dp));
    return count_dp(0, 10, 1, 1);  // prev = 10 (no digit yet)
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1) << endl;
    return 0;
}

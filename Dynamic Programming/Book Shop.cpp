#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);  // h = prices, s = pages
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> s[i];

    vector<int> dp(x + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = x; j >= h[i]; --j) {
            dp[j] = max(dp[j], dp[j - h[i]] + s[i]);
        }
    }

    cout << dp[x] << "\n";
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for (int &x : A) cin >> x;
    for (int &x : B) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (A[i-1] == B[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    // Reconstruct the sequence
    vector<int> lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (A[i-1] == B[j-1]) {
            lcs.push_back(A[i-1]);
            --i; --j;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(lcs.begin(), lcs.end());

    cout << dp[n][m] << "\n";
    for (int x : lcs) cout << x << " ";
    cout << "\n";
    return 0;
}

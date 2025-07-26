#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

long long dp[MAXN][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // dp[i][0] = ways to fill first i rows ending with two separate 1x1 blocks
    // dp[i][1] = ways to fill first i rows ending with one 2x1 horizontal block
    
    // Base case: for height 1
    dp[1][0] = 1;  // Two 1x1 blocks
    dp[1][1] = 1;  // One 2x1 block
    
    for (int i = 2; i < MAXN; i++) {
        // To have two 1x1 blocks at row i:
        // 1. Extend two 1x1 blocks from row i-1 (2 ways: both extend or place new 1x1s)
        // 2. Place two 1x1 blocks after a 2x1 block from row i-1 (1 way)
        // 3. Additional ways to split and arrange
        dp[i][0] = (4 * dp[i-1][0] + dp[i-1][1]) % MOD;
        
        // To have one 2x1 block at row i:
        // 1. Place 2x1 block after two 1x1 blocks from row i-1 (1 way)
        // 2. Extend or place new 2x1 block after previous 2x1 block (2 ways)
        dp[i][1] = (dp[i-1][0] + 2 * dp[i-1][1]) % MOD;
    }
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        long long ans = (dp[n][0] + dp[n][1]) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}

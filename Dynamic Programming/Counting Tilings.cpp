#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int n, m;
map<pair<int, int>, ll> memo;

ll solve(int col, int mask) {
    // Base case: reached end of grid
    if (col == m) {
        return mask == 0 ? 1 : 0;
    }
    
    // Check memoization
    if (memo.count({col, mask})) {
        return memo[{col, mask}];
    }
    
    ll result = 0;
    
    // Generate all valid ways to fill current column
    function<void(int, int, int)> generate = [&](int pos, int current_mask, int next_mask) {
        if (pos == n) {
            result = (result + solve(col + 1, next_mask)) % MOD;
            return;
        }
        
        if (current_mask & (1 << pos)) {
            // Cell already filled by horizontal tile from previous column
            generate(pos + 1, current_mask, next_mask);
        } else {
            // Cell is empty, need to fill it
            
            // Option 1: Place vertical tile (2x1)
            if (pos + 1 < n && !(current_mask & (1 << (pos + 1)))) {
                generate(pos + 2, current_mask | (1 << pos) | (1 << (pos + 1)), next_mask);
            }
            
            // Option 2: Place horizontal tile (1x2)
            generate(pos + 1, current_mask | (1 << pos), next_mask | (1 << pos));
        }
    };
    
    generate(0, mask, 0);
    return memo[{col, mask}] = result;
}

int main() {
    cin >> n >> m;
    cout << solve(0, 0) << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    FAST_IO;
    int n;
    cin >> n;
    
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result = (result * 2) % MOD;
    }
    
    cout << result << endl;
    return 0;
}

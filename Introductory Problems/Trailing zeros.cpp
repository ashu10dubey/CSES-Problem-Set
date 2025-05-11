#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define int long long

int32_t main() {
    FAST_IO;
    int n;
    cin >> n;
    
    int count = 0;
    for (int i = 5; i <= n; i *= 5) {
        count += n / i;
    }
    
    cout << count << endl;
    return 0;
}

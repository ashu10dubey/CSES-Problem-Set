#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    long long sum = 0, max_t = 0;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        sum += x;
        max_t = max(max_t, x);
    }
    cout << max(sum, 2 * max_t - sum) << "\n";
    // Or simply:
    // cout << max(sum, max_t) << "\n";
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    long long x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<int> arr(n);
    arr[0] = x % c;
    for (int i = 1; i < n; i++) {
        arr[i] = (1LL * a * arr[i-1] + b) % c;
    }

    const int BITS = 31;
    vector<int> expire(BITS, -1);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int val = arr[i];
        for (int bit = 0; bit < BITS; bit++) {
            if (val & (1 << bit)) {
                expire[bit] = i + k - 1;
            }
        }

        if (i >= k - 1) {
            int window_or = 0;
            for (int bit = 0; bit < BITS; bit++) {
                if (expire[bit] >= i) window_or |= (1 << bit);
            }
            ans ^= window_or;
        }
    }

    cout << ans << "\n";
    return 0;
}

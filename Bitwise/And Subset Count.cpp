#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9+7;

ll modexp(ll a, ll e = MOD-2) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int M = 0;
    for (int x : a) M = max(M, x);
    // Calculate minimum mask size as bit-length covering up to max(a) or n
    int LOG = 0;
    while ((1 << LOG) <= M) LOG++;
    int H = 1 << LOG;

    vector<int> cnt(H, 0);
    for (int x : a) cnt[x]++;

    // SOS DP to compute how many a_i have (a_i & k) == k
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < H; mask++) {
            if (!(mask & (1 << i))) {
                cnt[mask] += cnt[mask | (1 << i)];
            }
        }
    }

    vector<ll> f(H, 0);
    for (int mask = 0; mask < H; mask++) {
        if (cnt[mask] == 0) continue;
        f[mask] = (modexp(2, cnt[mask]) - 1 + MOD) % MOD;
    }

    // Inclusion–exclusion via SOS DP from supersets
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < H; mask++) {
            if (!(mask & (1 << i))) {
                f[mask] = (f[mask] - f[mask | (1 << i)] + MOD) % MOD;
            }
        }
    }

    // Output f[k] for k = 0..n
    for (int k = 0; k <= n; k++) {
        ll ans = (k < H ? f[k] : 0);
        cout << ans << (k == n ? '\n' : ' ');
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9+7;
const int MAXN = 2e5 + 5;

// Fenwick Tree (1-based indexing)
struct Fenwick {
    vector<ll> bit;
    Fenwick(int n) { bit.assign(n + 2, 0); }
    
    void update(int i, ll val) {
        while (i < bit.size()) {
            bit[i] = (bit[i] + val) % MOD;
            i += i & -i;
        }
    }
    
    ll query(int i) {
        ll res = 0;
        while (i > 0) {
            res = (res + bit[i]) % MOD;
            i -= i & -i;
        }
        return res;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> comp;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        comp.push_back(a[i]);
    }

    // Coordinate compression
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (int &x : a)
        x = lower_bound(comp.begin(), comp.end(), x) - comp.begin() + 1;

    Fenwick bit(comp.size());
    ll total = 0;

    for (int i = 0; i < n; ++i) {
        ll cnt = bit.query(a[i] - 1);  // count of subsequences ending at smaller elements
        ll add = (cnt + 1) % MOD;      // include subsequence [a[i]] itself
        bit.update(a[i], add);         // update dp value at a[i]
        total = (total + add) % MOD;
    }

    cout << total << "\n";
    return 0;
}

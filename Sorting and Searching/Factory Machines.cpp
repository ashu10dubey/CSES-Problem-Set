#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

bool canMake(const vector<ll> &machines, ll time, ll t) {
    ll total = 0;
    for (ll k : machines) {
        total += time / k;
        if (total >= t) return true;
    }
    return false;
}

int main() {
    int n;
    ll t;
    cin >> n >> t;

    vector<ll> machines(n);
    for (int i = 0; i < n; ++i) {
        cin >> machines[i];
    }

    ll lo = 0, hi = 1e18, ans = -1;

    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (canMake(machines, mid, t)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << "\n";
    return 0;
}

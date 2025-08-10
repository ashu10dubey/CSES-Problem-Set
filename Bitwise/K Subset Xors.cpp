#include <bits/stdc++.h>
using namespace std;

static vector<unsigned int> build_basis(const vector<unsigned int>& a) {
    const int B = 31;
    vector<unsigned int> basis(B, 0);
    for (auto x : a) {
        unsigned int v = x;
        for (int b = B - 1; b >= 0; --b) {
            if (((v >> b) & 1u) == 0) continue;
            if (!basis[b]) { basis[b] = v; break; }
            v ^= basis[b];
        }
    }
    vector<unsigned int> vecs;
    for (int b = B - 1; b >= 0; --b) if (basis[b]) vecs.push_back(basis[b]);
    int m = (int)vecs.size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            int msb = 31 - __builtin_clz(vecs[j]);
            if ((vecs[i] >> msb) & 1u) vecs[i] ^= vecs[j];
        }
    }
    vector<unsigned int> res;
    for (auto v : vecs) if (v) res.push_back(v);
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<unsigned int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<unsigned int> basis = build_basis(a);
    int r = (int)basis.size();

    vector<unsigned int> out;
    out.reserve(k);

    if (r == 0) {
        for (int i = 0; i < k; ++i) out.push_back(0);
    } else {
        vector<unsigned int> v = basis;
        vector<unsigned int> unique_vals;
        unique_vals.reserve(min(k, 1 << min(r, 20)));
        struct HNode { unsigned int val; int i; };
        struct HCmp { bool operator()(const HNode& a, const HNode& b) const { return a.val > b.val; } };
        priority_queue<HNode, vector<HNode>, HCmp> hq;

        unique_vals.push_back(0u);
        if (k > 1) {
            hq.push({v[0], 0});
            while ((int)unique_vals.size() < k && !hq.empty()) {
                auto cur = hq.top(); hq.pop();
                unique_vals.push_back(cur.val);
                int i = cur.i;
                if (i + 1 < r) {
                    hq.push({cur.val ^ v[i] ^ v[i+1], i + 1});
                    hq.push({cur.val ^ v[i+1], i + 1});
                }
            }
        }

        int redundant = n - r;
        long long mult = 1;
        while (redundant-- > 0) {
            if (mult > (long long)2e5) { mult = (long long)2e5 + 1; break; }
            mult <<= 1;
        }

        for (auto x : unique_vals) {
            long long times = min<long long>(mult, k - (int)out.size());
            for (long long t = 0; t < times; ++t) out.push_back(x);
            if ((int)out.size() >= k) break;
        }
        while ((int)out.size() < k && !hq.empty()) {
            auto cur = hq.top(); hq.pop();
            unsigned int val = cur.val;
            int i = cur.i;
            if (i + 1 < r) {
                hq.push({val ^ v[i] ^ v[i+1], i + 1});
                hq.push({val ^ v[i+1], i + 1});
            }
            long long times = min<long long>(mult, k - (int)out.size());
            for (long long t = 0; t < times; ++t) out.push_back(val);
        }
    }

    for (int i = 0; i < k; ++i) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << '\n';
    return 0;
}

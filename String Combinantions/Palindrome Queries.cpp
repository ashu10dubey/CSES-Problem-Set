#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const int MOD = 1'000'000'007;

// Fenwick Tree for modular sums
struct BIT {
    int n;
    vector<int> bit;
    BIT() {}
    BIT(int n): n(n), bit(n+1, 0) {}

    static inline int addmod(int a, int b) {
        int s = a + b;
        if (s >= MOD) s -= MOD;
        return s;
    }
    static inline int submod(int a, int b) {
        int s = a - b;
        if (s < 0) s += MOD;
        return s;
    }

    void add(int idx, int val) {
        // idx is 1-based
        while (idx <= n) {
            bit[idx] = addmod(bit[idx], val);
            idx += idx & -idx;
        }
    }

    int sum(int idx) const {
        int res = 0;
        while (idx > 0) {
            int v = bit[idx];
            res += v;
            if (res >= MOD) res -= MOD;
            idx -= idx & -idx;
        }
        return res;
    }

    int range_sum(int l, int r) const {
        if (l > r) return 0;
        int s = sum(r) - sum(l-1);
        if (s < 0) s += MOD;
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    string s;
    cin >> s;

    // Choose base; a fixed good base is fine. Randomizing is optional.
    // Using 911382323 is too big; pick something like 911382323 mod is 911382323 but close to MOD, not ideal.
    // Common safe small base:
    int base = 911382323; // We'll replace with randomized in [73, 1e6) but mod safe after %MOD.
    {
        // Randomize base in a reasonable range to reduce collisions
        mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> dist(73, 1000000);
        base = dist(rng);
    }

    // Precompute powers of base up to n
    vector<int> pwr(n+1, 1);
    for (int i = 1; i <= n; ++i) {
        pwr[i] = (ll)pwr[i-1] * base % MOD;
    }

    // Two BITs: forward hash uses weight base^i, backward uses base^(n-1-i)
    BIT fwd(n), bwd(n);

    auto val = [](char c) -> int { return (c - 'a' + 1); };

    for (int i = 0; i < n; ++i) {
        int v = val(s[i]);
        // positions in BIT are 1-based
        fwd.add(i+1, (int)((ll)v * pwr[i] % MOD));
        bwd.add(i+1, (int)((ll)v * pwr[n-1-i] % MOD));
    }

    auto get_hash_fwd = [&](int l, int r) -> int {
        // l,r are 1-based inclusive
        // sum of v[i]*base^i for i in [l-1..r-1]
        int raw = fwd.range_sum(l, r);
        // normalize to start at exponent 0: multiply by base^(n-1 - (r-1))? No.
        // We want to shift so that exponent becomes 0-based at l: divide by base^(l-1), i.e., multiply by inverse.
        // But we don't have inverses; instead, align by comparing both sides equally using multiplication by powers.
        // For comparison, we'll align outside by multiplying with pwr[n-1 - r + 1] etc.
        // Here, just return raw; caller aligns both hashes with same exponent.
        return raw;
    };

    auto get_hash_bwd = [&](int l, int r) -> int {
        // sum of v[i]*base^(n-1-i) for i in [l-1..r-1]
        int raw = bwd.range_sum(l, r);
        return raw;
    };

    // For comparing s[a..b] with its reverse:
    // Forward part Hf = sum v[i]*base^i, i in [a-1..b-1]
    // Backward part Hb = sum v[i]*base^(n-1-i), i in [a-1..b-1]
    // To compare, we need both hashes representing the substring with the same exponent origin.
    // Multiply Hf by base^(n-1 - (b-1)) = base^(n-b) so exponents become base^(i + (n-b)) -> for i=a-1 => base^(n - (b-(a-1))) = base^(n - (len + a - 1 - (a -1))) = base^(n-len).
    // Multiply Hb by base^((a-1)) so exponents become base^(n-1-i + (a-1)); for i=a-1 => base^(n-1-(a-1)+(a-1)) = base^(n-1); for i=b-1 => base^(n-1-(b-1)+(a-1)) = base^(n-b+a-1) = base^(n-len).
    // Thus both aligned to same highest power; equality holds if and only if palindrome.

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k; char x;
            cin >> k >> x;
            int oldv = val(s[k-1]);
            int newv = val(x);

            // Remove old contribution
            fwd.add(k, (int)((MOD - (ll)oldv * pwr[k-1] % MOD) % MOD));
            bwd.add(k, (int)((MOD - (ll)oldv * pwr[n - k] % MOD) % MOD));
            // Add new contribution
            fwd.add(k, (int)((ll)newv * pwr[k-1] % MOD));
            bwd.add(k, (int)((ll)newv * pwr[n - k] % MOD));

            s[k-1] = x;
        } else {
            int a, b;
            cin >> a >> b;
            int hf = get_hash_fwd(a, b);
            int hb = get_hash_bwd(a, b);

            // Align exponents
            int len = b - a + 1;
            int mulF = pwr[n - b];     // base^(n-b)
            int mulB = pwr[a - 1];     // base^(a-1)

            int lhs = (ll)hf * mulF % MOD;
            int rhs = (ll)hb * mulB % MOD;

            cout << (lhs == rhs ? "YES\n" : "NO\n");
        }
    }
    return 0;
}

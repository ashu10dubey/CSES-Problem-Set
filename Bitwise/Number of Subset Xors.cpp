#include <bits/stdc++.h>
using namespace std;

const int MAX_BITS = 60;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    // Build XOR basis
    vector<long long> basis(MAX_BITS, 0);
    for (long long x : a) {
        for (int i = MAX_BITS - 1; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    break;
                } else {
                    x ^= basis[i];
                }
            }
        }
    }

    // Count the number of non-zero basis vectors
    int rank = 0;
    for (int i = 0; i < MAX_BITS; ++i)
        if (basis[i]) rank++;

    // The number of distinct subset xors is 2^rank
    cout << (1LL << rank) << '\n';
    return 0;
}

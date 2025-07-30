#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    vector<long long> basis(64, 0); // Up to 60 bits for safety

    for (long long num : a) {
        for (int i = 60; i >= 0; --i) {
            if ((num >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = num;
                    break;
                }
                num ^= basis[i];
            }
        }
    }

    // Maximum subset XOR is XOR of all basis elements greedily
    long long res = 0;
    for (int i = 60; i >= 0; --i)
        if ((res ^ basis[i]) > res)
            res ^= basis[i];

    cout << res << '\n';
    return 0;
}

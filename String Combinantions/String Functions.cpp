#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    // Z-function
    vector<int> z(n, 0);
    int l = 0, r = 0; // [l, r) current Z-box, r is exclusive in this variant
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    // Problem requires z(1)=0, which matches z[0]=0 in 0-based indexing[1].

    // Prefix-function (KMP)
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }

    // Output
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << z[i];
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << pi[i];
    }
    cout << '\n';
    return 0;
}

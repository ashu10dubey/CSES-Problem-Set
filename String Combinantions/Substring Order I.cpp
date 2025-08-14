#include <bits/stdc++.h>
using namespace std;

// Build suffix array in O(n log n)
vector<int> build_sa(const string &s) {
    int n = s.size();
    vector<int> sa(n), rnk(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rnk[i] = s[i];
    }
    vector<int> tmp(n);
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
            int ra = (a + k < n) ? rnk[a + k] : -1;
            int rb = (b + k < n) ? rnk[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rnk = tmp;
        if (rnk[sa[n - 1]] == n - 1) break; // all ranks unique
    }
    return sa;
}

// Build LCP array in O(n)
vector<int> build_lcp(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rnk(n), lcp(n);
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rnk[i] > 0) {
            int j = sa[rnk[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rnk[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    long long k;
    cin >> s >> k;

    // Build SA and LCP
    vector<int> sa = build_sa(s);
    vector<int> lcp = build_lcp(s, sa);

    int n = s.size();
    for (int i = 0; i < n; i++) {
        long long total_suffix = n - sa[i];
        long long new_here = total_suffix - lcp[i]; // new substrings from this suffix
        if (k > new_here) {
            k -= new_here;
        } else {
            long long len = lcp[i] + k;
            cout << s.substr(sa[i], len) << "\n";
            return 0;
        }
    }
}

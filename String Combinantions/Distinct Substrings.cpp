#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

void count_sort(vector<int> &p, vector<int> &c) {
    int n = p.size();
    vector<int> cnt(n);
    for (auto x : c) cnt[x]++;
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];
    for (auto x : p) {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

vector<int> build_suffix_array(string s) {
    s += "$";
    int n = s.size();
    vector<int> p(n), c(n);
    vector<pair<char, int>> a(n);
    for(int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for(int i = 1; i < n; i++) c[p[i]] = c[p[i-1]] + (a[i].first != a[i-1].first);
    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        count_sort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
            pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i-1]] + (now != prev);
        }
        c = c_new;
        k++;
    }
    return p;
}

vector<int> build_lcp_array(const string& s, const vector<int>& sa) {
    int n = s.length();
    vector<int> rank(n);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    vector<int> lcp(n, 0);
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = sa[rank[i] - 1];
            if (h > 0) h--;
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rank[i]] = h;
        }
    }
    return lcp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s_orig;
    cin >> s_orig;
    long long n = s_orig.length();
    vector<int> sa = build_suffix_array(s_orig);
    vector<int> lcp = build_lcp_array(s_orig + "$", sa);
    long long total_substrings = n * (n + 1) / 2;
    long long duplicate_substrings = 0;
    for (size_t i = 1; i < lcp.size(); ++i) duplicate_substrings += lcp[i];
    cout << total_substrings - duplicate_substrings << endl;
    return 0;
}

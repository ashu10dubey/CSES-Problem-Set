#include <bits/stdc++.h>
using namespace std;

struct SAM {
    struct State {
        int link = -1;
        int len = 0;
        int next[26];
        long long occ = 0;    // number of end positions (occurrence count)
        long long ways = -1;  // DP: total weighted non-empty paths from this state
        State() { memset(next, -1, sizeof next); }
    };

    vector<State> st;
    int last;

    SAM(int n = 0) {
        st.reserve(2*n + 5);
        st.push_back(State());
        last = 0;
    }

    void extend(char ch) {
        int c = ch - 'a';
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].occ = 1; // new end position
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);              // clone q
                st[clone].len = st[p].len + 1;
                st[clone].occ = 0;                // clones don't add new end positions
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    void compute_occ() {
        int m = (int)st.size();
        int maxLen = 0;
        for (auto &x : st) maxLen = max(maxLen, x.len);
        vector<int> cnt(maxLen + 1, 0), order(m);
        for (int i = 0; i < m; ++i) cnt[st[i].len]++;
        for (int i = 1; i <= maxLen; ++i) cnt[i] += cnt[i - 1];
        for (int i = m - 1; i >= 0; --i) order[--cnt[st[i].len]] = i; // increasing by len
        // propagate in decreasing length order (skip state 0’s parent which is -1)
        for (int i = m - 1; i > 0; --i) {
            int v = order[i];
            int p = st[v].link;
            if (p >= 0) st[p].occ += st[v].occ;
        }
    }

    long long dfs_ways(int v) {
        if (st[v].ways != -1) return st[v].ways;
        long long res = 0;
        for (int c = 0; c < 26; ++c) {
            int u = st[v].next[c];
            if (u == -1) continue;
            // taking edge c contributes current-length substring count (occ[u])
            // and all longer substrings continuing from u (ways[u])
            res += st[u].occ;
            res += dfs_ways(u);
        }
        st[v].ways = res;
        return res;
    }

    string kth_substring(long long k) {
        compute_occ();
        dfs_ways(0);
        string ans;
        int v = 0;
        while (k > 0) {
            bool progressed = false;
            for (int c = 0; c < 26; ++c) {
                int u = st[v].next[c];
                if (u == -1) continue;
                long long block = st[u].occ + st[u].ways;
                if (k > block) {
                    k -= block;
                } else {
                    // choose this edge
                    ans.push_back(char('a' + c));
                    if (k <= st[u].occ) {
                        // the current prefix is exactly the k-th substring
                        return ans;
                    } else {
                        k -= st[u].occ;
                        v = u;
                        progressed = true;
                        break;
                    }
                }
            }
            // k is guaranteed valid; this guard avoids infinite loops in unexpected cases
            if (!progressed) break;
        }
        return ans; // per problem, k is valid, so we should have returned earlier
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    long long k;
    if (!(cin >> s)) return 0;
    cin >> k;

    SAM sam((int)s.size());
    for (char ch : s) sam.extend(ch);

    cout << sam.kth_substring(k) << '\n';
    return 0;
}

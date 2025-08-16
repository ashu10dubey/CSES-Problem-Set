#include <bits/stdc++.h>
using namespace std;

struct SAM {
    struct State {
        int link = -1;
        int len = 0;
        int next[26];
        State() { memset(next, -1, sizeof next); }
    };
    vector<State> st;
    int last;
    SAM(int n = 0) {
        st.reserve(2 * n + 5);
        st.push_back(State());
        last = 0;
    }
    void extend(char ch) {
        int c = ch - 'a';
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
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
                st.push_back(st[q]);          // copy q
                st[clone].len = st[p].len + 1;
                // clone inherits next[] and link from q; do not copy anything else
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    SAM sam(n);
    for (char ch : s) sam.extend(ch);

    // Difference array for lengths 1..n
    vector<long long> diff(n + 2, 0);

    // For each state v != 0, add +1 to interval [minlen(v), len(v)]
    for (int v = 1; v < (int)sam.st.size(); ++v) {
        int L = sam.st[sam.st[v].link].len + 1; // minlen(v)
        int R = sam.st[v].len;                  // len(v)
        if (L <= R) {
            if (L <= n) diff[L] += 1;
            if (R + 1 <= n) diff[R + 1] -= 1;
        }
    }

    // Prefix sum to get counts per length 1..n
    long long cur = 0;
    for (int len = 1; len <= n; ++len) {
        cur += diff[len];
        if (len > 1) cout << ' ';
        cout << cur;
    }
    cout << '\n';
    return 0;
}

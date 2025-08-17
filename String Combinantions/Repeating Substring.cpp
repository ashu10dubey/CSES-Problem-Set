#include <bits/stdc++.h>
using namespace std;

struct SAM {
    struct State {
        int link = -1;
        int len = 0;
        int next[26];
        int occ = 0; // number of end positions reaching this state
        State() {
            fill(begin(next), end(next), -1);
        }
    };

    vector<State> st;
    int last = 0;

    SAM(int n = 0) {
        st.reserve(2 * max(1, n));
        st.push_back(State()); // initial state 0
        last = 0;
    }

    void extend(int c) {
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].occ = 1;

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
                st[clone].occ = 0;            // clones do not represent new end positions
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

    // Propagate occurrence counts along suffix links in order of decreasing length
    void finalize_occ() {
        int maxLen = 0;
        for (auto &x : st) maxLen = max(maxLen, x.len);

        vector<int> cnt(maxLen + 1, 0);
        for (auto &x : st) cnt[x.len]++;

        for (int i = 1; i <= maxLen; ++i) cnt[i] += cnt[i - 1];

        vector<int> order(st.size());
        for (int i = (int)st.size() - 1; i >= 0; --i) {
            order[--cnt[st[i].len]] = i;
        }

        // from longer to shorter (skip i=0 because it's the smallest len)
        for (int i = (int)order.size() - 1; i > 0; --i) {
            int v = order[i];
            int p = st[v].link;
            if (p >= 0) st[p].occ += st[v].occ;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    SAM sam(n);
    for (char ch : s) sam.extend(ch - 'a');
    sam.finalize_occ();

    // Find longest length with at least two occurrences
    int bestLen = 0;
    for (auto &x : sam.st) if (x.occ >= 2) bestLen = max(bestLen, x.len);

    if (bestLen == 0) {
        cout << -1 << '\n';
        return 0;
    }

    // Reconstruct any one occurrence:
    // Walk the string maintaining current state and current matched length.
    // Keep end position when matched length >= bestLen and state has occ >= 2.
    int v = 0, l = 0, endPos = -1;
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        if (sam.st[v].next[c] != -1) {
            v = sam.st[v].next[c];
            l++;
        } else {
            while (v != -1 && sam.st[v].next[c] == -1) v = sam.st[v].link;
            if (v == -1) { v = 0; l = 0; continue; }
            l = sam.st[v].len + 1;
            v = sam.st[v].next[c];
        }
        // If current matched length exceeds bestLen, shrink via suffix links
        while (sam.st[v].link != -1 && sam.st[sam.st[v].link].len >= bestLen) {
            v = sam.st[v].link;
            l = sam.st[v].len;
        }
        if (l >= bestLen && sam.st[v].occ >= 2) {
            endPos = i;
            break; // found one
        }
    }

    // Fallback (very unlikely): be more permissive/careful if not found on first pass
    if (endPos == -1) {
        v = 0; l = 0;
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (sam.st[v].next[c] != -1) {
                v = sam.st[v].next[c];
                l++;
            } else {
                while (v != -1 && sam.st[v].next[c] == -1) v = sam.st[v].link;
                if (v == -1) { v = 0; l = 0; continue; }
                l = sam.st[v].len + 1;
                v = sam.st[v].next[c];
            }
            // cap l to bestLen
            while (l > bestLen) { v = sam.st[v].link; l = sam.st[v].len; }
            if (l == bestLen && sam.st[v].occ >= 2) { endPos = i; break; }
        }
    }

    // By problem logic, endPos should be set if bestLen > 0
    if (endPos == -1) {
        // As a last resort (should not happen), print any valid length bestLen by scanning again
        // but to keep it simple, print -1 (defensive). In practice, above should find it.
        cout << -1 << '\n';
        return 0;
    }

    cout << s.substr(endPos - bestLen + 1, bestLen) << '\n';
    return 0;
}

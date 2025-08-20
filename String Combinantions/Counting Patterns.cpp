#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int MAX_NODES = 1000006;
const int ALPHABET_SIZE = 26;

int trie[MAX_NODES][ALPHABET_SIZE];
int fail[MAX_NODES];
long long match_counts[MAX_NODES];
int pattern_end_node[500005];
int node_count = 1;

void insert(const string& s, int pattern_idx) {
    int curr = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[curr][c] == 0) {
            trie[curr][c] = node_count++;
        }
        curr = trie[curr][c];
    }
    pattern_end_node[pattern_idx] = curr;
}

vector<int> build_failure_links() {
    queue<int> q;
    vector<int> bfs_order;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfs_order.push_back(u);
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            int v = trie[u][i];
            if (v == 0) continue;
            int f = fail[u];
            while (f > 0 && trie[f][i] == 0) {
                f = fail[f];
            }
            if (trie[f][i]) {
                fail[v] = trie[f][i];
            }
            q.push(v);
        }
    }
    return bfs_order;
}

int main() {
    fast_io();
    string text;
    cin >> text;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string pattern;
        cin >> pattern;
        insert(pattern, i);
    }
    vector<int> bfs_order = build_failure_links();
    int curr_node = 0;
    for (char ch : text) {
        int c = ch - 'a';
        while (curr_node > 0 && trie[curr_node][c] == 0) {
            curr_node = fail[curr_node];
        }
        if (trie[curr_node][c]) {
            curr_node = trie[curr_node][c];
        }
        match_counts[curr_node]++;
    }
    for (int i = bfs_order.size() - 1; i >= 0; --i) {
        int u = bfs_order[i];
        match_counts[fail[u]] += match_counts[u];
    }
    for (int i = 0; i < k; ++i) {
        cout << match_counts[pattern_end_node[i]] << "\n";
    }
    return 0;
}

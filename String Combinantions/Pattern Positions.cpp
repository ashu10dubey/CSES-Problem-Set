#include <bits/stdc++.h>

using namespace std;

const int MAX_NODES = 1000006;
const int ALPHABET_SIZE = 26;

int trie[MAX_NODES][ALPHABET_SIZE];
int fail[MAX_NODES];
int node_count = 1;

vector<pair<int, int>> patterns_at_node[MAX_NODES];
vector<int> fail_tree_adj[MAX_NODES];
int first_visit[MAX_NODES];

void insert(const string& s, int pattern_idx) {
    int curr = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[curr][c] == 0) {
            trie[curr][c] = node_count++;
        }
        curr = trie[curr][c];
    }
    patterns_at_node[curr].push_back({pattern_idx, (int)s.length()});
}

void build_failure_links() {
    queue<int> q;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            int v = trie[u][i];
            if (v == 0) continue;
            int f = fail[u];
            while (f > 0 && trie[f][i] == 0) f = fail[f];
            if (trie[f][i]) fail[v] = trie[f][i];
            q.push(v);
        }
    }
}

void dfs_fail_tree(int u) {
    for (int v : fail_tree_adj[u]) {
        dfs_fail_tree(v);
        first_visit[u] = min(first_visit[u], first_visit[v]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    cin >> text;
    int n = text.length();

    int k;
    cin >> k;

    for (int i = 0; i < k; ++i) {
        string pattern;
        cin >> pattern;
        insert(pattern, i);
    }

    build_failure_links();
    
    fill(first_visit, first_visit + node_count, n + 1);

    int curr_node = 0;
    for (int i = 0; i < n; ++i) {
        int c = text[i] - 'a';
        while (curr_node > 0 && trie[curr_node][c] == 0) {
            curr_node = fail[curr_node];
        }
        if (trie[curr_node][c]) {
            curr_node = trie[curr_node][c];
        }
        first_visit[curr_node] = min(first_visit[curr_node], i);
    }
    
    for (int i = 1; i < node_count; ++i) {
        fail_tree_adj[fail[i]].push_back(i);
    }
    dfs_fail_tree(0);

    vector<int> answers(k, -1);
    for (int i = 0; i < node_count; ++i) {
        if (first_visit[i] <= n) {
            for (auto const& [p_idx, p_len] : patterns_at_node[i]) {
                int start_pos = first_visit[i] - p_len + 2;
                if (answers[p_idx] == -1) {
                     answers[p_idx] = start_pos;
                }
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << answers[i] << "\n";
    }

    return 0;
}
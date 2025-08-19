#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int ALPHABET_SIZE = 26;

struct Node {
    int next[ALPHABET_SIZE];
    int go[ALPHABET_SIZE];
    int link;
    vector<int> pattern_indices;
    Node() {
        fill(next, next + ALPHABET_SIZE, 0);
        fill(go, go + ALPHABET_SIZE, 0);
        link = 0;
    }
};

vector<Node> trie;
vector<int> end_node_map;

void add_string(const string& s, int pattern_idx) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == 0) {
            trie[v].next[c] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].pattern_indices.push_back(pattern_idx);
    end_node_map[pattern_idx] = v;
}

int main() {
    fast_io();
    string text;
    cin >> text;
    int k;
    cin >> k;
    trie.emplace_back();
    end_node_map.resize(k);
    for (int i = 0; i < k; ++i) {
        string pattern;
        cin >> pattern;
        add_string(pattern, i);
    }
    queue<int> q;
    vector<int> bfs_order;
    bfs_order.reserve(trie.size());
    for (int c = 0; c < ALPHABET_SIZE; ++c) {
        if (trie[0].next[c]) {
            q.push(trie[0].next[c]);
        }
        trie[0].go[c] = trie[0].next[c];
    }
    bfs_order.push_back(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfs_order.push_back(u);
        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            if (trie[u].next[c]) {
                int v = trie[u].next[c];
                trie[v].link = trie[trie[u].link].go[c];
                trie[u].go[c] = v;
                q.push(v);
            } else {
                trie[u].go[c] = trie[trie[u].link].go[c];
            }
        }
    }
    vector<int> match_count(trie.size(), 0);
    int current_node = 0;
    for (char ch : text) {
        current_node = trie[current_node].go[ch - 'a'];
        match_count[current_node]++;
    }
    for (int i = bfs_order.size() - 1; i > 0; --i) {
        int u = bfs_order[i];
        match_count[trie[u].link] += match_count[u];
    }
    for (int i = 0; i < k; ++i) {
        int node_idx = end_node_map[i];
        if (match_count[node_idx] > 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

struct TrieNode {
    TrieNode* children[26];
    bool is_end = false;
    TrieNode() {
        fill(begin(children), end(children), nullptr);
    }
};

void insert(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int idx = ch - 'a';
        if (!node->children[idx])
            node->children[idx] = new TrieNode();
        node = node->children[idx];
    }
    node->is_end = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int k;
    cin >> s >> k;
    int n = s.size();

    TrieNode* root = new TrieNode();
    while (k--) {
        string word;
        cin >> word;
        insert(root, word);
    }

    vector<int> dp(n + 1);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        if (dp[i] == 0) continue;
        TrieNode* node = root;
        for (int j = i; j < n; ++j) {
            int idx = s[j] - 'a';
            if (!node->children[idx]) break;
            node = node->children[idx];
            if (node->is_end)
                dp[j + 1] = (dp[j + 1] + dp[i]) % MOD;
        }
    }

    cout << dp[n] << '\n';
    return 0;
}

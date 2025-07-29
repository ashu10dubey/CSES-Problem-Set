#include <bits/stdc++.h>
using namespace std;

const int MAX_BITS = 31;  // because 10^9 fits in 30 bits

struct TrieNode {
    TrieNode* next[2];
    TrieNode() { next[0] = next[1] = nullptr; }
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(int num) {
        TrieNode* node = root;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!node->next[bit])
                node->next[bit] = new TrieNode();
            node = node->next[bit];
        }
    }

    int getMaxXor(int num) {
        TrieNode* node = root;
        int maxXor = 0;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int opposite = bit ^ 1;
            if (node->next[opposite]) {
                maxXor |= (1 << i);
                node = node->next[opposite];
            } else {
                node = node->next[bit];
            }
        }
        return maxXor;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    Trie trie;
    trie.insert(0);  // insert base prefix XOR 0

    int prefixXor = 0, result = 0;
    for (int x : a) {
        prefixXor ^= x;
        result = max(result, trie.getMaxXor(prefixXor));
        trie.insert(prefixXor);
    }

    cout << result << endl;
    return 0;
}

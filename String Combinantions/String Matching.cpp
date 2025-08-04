#include <bits/stdc++.h>
using namespace std;

// Function to build the prefix array (pi function)
vector<int> computePrefix(string& pattern) {
    int m = pattern.size();
    vector<int> pi(m);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pattern;
    cin >> text >> pattern;

    int n = text.size(), m = pattern.size();
    vector<int> pi = computePrefix(pattern);

    int count = 0;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == m) {
            count++;
            j = pi[j - 1]; // Continue to look for next match
        }
    }

    cout << count << '\n';
    return 0;
}

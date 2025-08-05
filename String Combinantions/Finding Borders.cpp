#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    vector<int> pi(n);

    // Compute prefix function
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }

    // Traverse the borders from the end
    vector<int> borders;
    int len = pi[n - 1];
    while (len > 0) {
        borders.push_back(len);
        len = pi[len - 1];
    }

    // Sort in increasing order
    reverse(borders.begin(), borders.end());

    for (int x : borders)
        cout << x << ' ';
    cout << '\n';
}

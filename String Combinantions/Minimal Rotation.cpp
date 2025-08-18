#include <bits/stdc++.h>
using namespace std;

// Booth's algorithm: returns starting index of lexicographically minimal rotation
static int least_rotation(const string &s) {
    int n = (int)s.size();
    if (n == 0) return 0;
    // Failure function over 2n
    vector<int> f(2 * n, -1);
    int k = 0; // current candidate start of minimal rotation
    for (int j = 1; j < 2 * n; ++j) {
        int i = f[j - k - 1];
        // Compare s[j % n] with s[(k + i + 1) % n], update k as needed
        while (i != -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[k % n]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k % n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    int k = least_rotation(s);
    int n = (int)s.size();
    // Output the minimal rotation
    // Use two substrings to avoid building a doubled string of size 2n in memory
    cout << s.substr(k) << s.substr(0, k) << '\n';
    return 0;
}

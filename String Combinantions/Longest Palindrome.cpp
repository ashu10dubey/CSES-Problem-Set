#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(const string &s) {
    int n = s.size();
    if (n == 0) return "";

    // Build transformed string with separators: ^#a#b#c#$
    string t = "@";
    for (char c : s) {
        t += "#";
        t += c;
    }
    t += "#$";

    int m = t.size();
    vector<int> p(m, 0);
    int center = 0, right = 0;
    int maxLen = 0, centerIndex = 0;

    for (int i = 1; i < m - 1; ++i) {
        int mirror = 2 * center - i;
        if (i < right)
            p[i] = min(right - i, p[mirror]);

        // Expand around center i
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]])
            p[i]++;

        // Update center and right boundary
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // Track max length
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    // Extract longest palindrome
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << longestPalindrome(s) << "\n";
    return 0;
}

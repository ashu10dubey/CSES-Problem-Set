#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'A']++;

    // Check if rearrangement is impossible
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > (n + 1) / 2) {
            cout << -1 << "\n";
            return 0;
        }
    }

    string result;
    int last_char = -1; // Index of last character used

    for (int i = 0; i < n; ++i) {
        // Try each character from 'A' to 'Z'
        bool found = false;
        for (int c = 0; c < 26; ++c) {
            if (freq[c] > 0 && c != last_char) {
                freq[c]--;
                // Check if remaining can form a valid string
                int max_count = 0, sum = 0;
                for (int x = 0; x < 26; ++x) {
                    sum += freq[x];
                    max_count = max(max_count, freq[x]);
                }
                if (max_count <= (sum + 1) / 2) {
                    result.push_back('A' + c);
                    last_char = c;
                    found = true;
                    break;
                }
                // Backtrack if invalid
                freq[c]++;
            }
        }
        if (!found) {
            cout << -1 << "\n";
            return 0;
        }
    }

    cout << result << "\n";
    return 0;
}


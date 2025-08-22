#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

const int MOD = 1e9 + 7;

// Computes the KMP failure function (LPS array)
vector<int> compute_lps(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int length = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Modular exponentiation to calculate (base^exp) % mod
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string p;
    cin >> p;
    int m = p.length();

    // 1. Pre-calculate the KMP automaton transitions
    vector<int> lps = compute_lps(p);
    vector<vector<int>> transitions(m, vector<int>(26));

    for (int j = 0; j < m; ++j) {
        for (char c_char = 'A'; c_char <= 'Z'; ++c_char) {
            int c = c_char - 'A';
            if (j > 0 && c_char != p[j]) {
                transitions[j][c] = transitions[lps[j - 1]][c];
            } else {
                if (c_char == p[j]) {
                    transitions[j][c] = j + 1;
                } else { // j == 0 and c_char != p[0]
                    transitions[j][c] = 0;
                }
            }
        }
    }

    // 2. DP to count strings *without* the pattern
    vector<vector<long long>> dp(n + 1, vector<long long>(m, 0));
    dp[0][0] = 1; // Base case

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dp[i][j] == 0) continue;
            for (int c = 0; c < 26; ++c) {
                int next_j = transitions[j][c];
                if (next_j < m) {
                    dp[i + 1][next_j] = (dp[i + 1][next_j] + dp[i][j]) % MOD;
                }
            }
        }
    }

    // 3. Sum up all valid strings of length n
    long long strings_without_pattern = 0;
    for (int j = 0; j < m; ++j) {
        strings_without_pattern = (strings_without_pattern + dp[n][j]) % MOD;
    }

    // 4. Calculate final answer
    long long total_strings = power(26, n);
    long long result = (total_strings - strings_without_pattern + MOD) % MOD;

    cout << result << endl;

    return 0;
}
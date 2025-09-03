#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // dp[0..3] correspond to 'A', 'C', 'G', 'T'
    // Stores the length of the shortest non-subsequence ending in that char.
    vector<long long> dp(4, 1);
    
    // To reconstruct, we store the previous dp values for each character update
    vector<vector<long long>> prev_dp(s.length(), vector<long long>(4));

    for (int i = 0; i < s.length(); ++i) {
        char current_char = s[i];
        int char_idx;
        if (current_char == 'A') char_idx = 0;
        else if (current_char == 'C') char_idx = 1;
        else if (current_char == 'G') char_idx = 2;
        else char_idx = 3; // 'T'

        // Store the state before the update for reconstruction
        prev_dp[i] = dp;

        // Find the minimum of the previous lengths
        long long min_len = LLONG_MAX;
        for (long long len : dp) {
            min_len = min(min_len, len);
        }

        // Update the dp for the current character
        dp[char_idx] = 1 + min_len;
    }

    // Find the final minimum length and the character that produces it
    long long final_min_len = LLONG_MAX;
    int last_char_idx = -1;
    for (int i = 0; i < 4; ++i) {
        if (dp[i] < final_min_len) {
            final_min_len = dp[i];
            last_char_idx = i;
        }
    }

    // Reconstruct the string by working backwards
    string result = "";
    long long target_len = final_min_len;

    for (int i = s.length() - 1; i >= 0; --i) {
        char current_char_in_s = s[i];
        int current_char_idx;
        if (current_char_in_s == 'A') current_char_idx = 0;
        else if (current_char_in_s == 'C') current_char_idx = 1;
        else if (current_char_in_s == 'G') current_char_idx = 2;
        else current_char_idx = 3;

        // Check if this was the step where our target character's dp value was set
        if (current_char_idx == last_char_idx && 1 + *min_element(prev_dp[i].begin(), prev_dp[i].end()) == target_len) {
            result += current_char_in_s;
            target_len--;
            
            // Find the new target character for the previous state
            long long prev_min_len = *min_element(prev_dp[i].begin(), prev_dp[i].end());
            for (int j = 0; j < 4; ++j) {
                if (prev_dp[i][j] == prev_min_len) {
                    last_char_idx = j;
                    break;
                }
            }
        }
    }
    // Add the first character
    string first_char = "";
    if (last_char_idx == 0) first_char = "A";
    else if (last_char_idx == 1) first_char = "C";
    else if (last_char_idx == 2) first_char = "G";
    else first_char = "T";
    result += first_char;

    reverse(result.begin(), result.end());
    cout << result << endl;

    return 0;
}
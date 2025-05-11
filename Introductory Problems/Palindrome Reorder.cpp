#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

int main() {
    FAST_IO;
    string s;
    cin >> s;
    
    // Frequency count of each character
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'A']++;
    }
    
    // Check if a palindrome is possible
    int odd_count = 0;
    char odd_char = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] % 2 == 1) {
            odd_count++;
            odd_char = 'A' + i;
        }
    }
    
    // A palindrome is possible only if at most one character has an odd frequency
    if (odd_count > 1) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    
    // Construct the palindrome
    string first_half = "", second_half = "";
    for (int i = 0; i < 26; ++i) {
        string part(freq[i] / 2, 'A' + i);
        first_half += part;
        second_half = part + second_half;
    }
    
    // Add the middle character if there's an odd frequency
    if (odd_count == 1) {
        first_half += odd_char;
    }
    
    // Print the complete palindrome
    cout << first_half + second_half << endl;
    return 0;
}

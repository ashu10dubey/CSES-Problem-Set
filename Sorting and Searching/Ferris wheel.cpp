#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast I/O
    cin.tie(nullptr);            // Untie cin from cout

    int n, x;
    cin >> n >> x; // n = number of children, x = max allowed weight per gondola

    vector<int> p(n);           // SC: O(n) - storing weights of n children
    for (int &w : p) cin >> w;  // Read weights

    sort(p.begin(), p.end());  // TC: O(n log n) - sorting the weights

    int i = 0, j = n - 1;       // Two pointers: lightest (i) and heaviest (j)
    int gondolas = 0;           // Counter for minimum gondolas required

    // TC: O(n) - each child is processed at most once
    while (i <= j) {
        if (p[i] + p[j] <= x) {
            // If the lightest and heaviest can ride together
            i++; // Include lightest
        }
        // Heaviest always boards a gondola
        j--;      // Reduce to next heaviest
        gondolas++; // Count this gondola
    }

    cout << gondolas << '\n'; // Final answer

    return 0;
}

/*
-------------------------------------------------------
Time Complexity (TC):
- Reading input: O(n)
- Sorting weights: O(n log n)
- Two-pointer iteration: O(n)
- Overall: O(n log n)

Space Complexity (SC):
- Input storage (weights): O(n)
- No auxiliary structures beyond that
- Overall: O(n)
-------------------------------------------------------
*/

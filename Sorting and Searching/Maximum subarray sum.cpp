#include <bits/stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Time Complexity: O(n)
// Space Complexity: O(1)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long max_sum = -1e18; // since elements can be as low as -1e9
    long long current_sum = 0;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        current_sum = max(x, current_sum + x);
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << '\n';
    return 0;
}

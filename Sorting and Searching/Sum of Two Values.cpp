#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> a(n);
    unordered_map<long long, int> seen; // stores value -> index

    for (int i = 0; i < n; ++i) {
        cin >> a[i];

        long long complement = x - a[i];
        if (seen.count(complement)) {
            // Found the pair, output 1-based indices
            cout << seen[complement] + 1 << " " << i + 1 << '\n';
            return 0;
        }
        // Store current value with its index
        seen[a[i]] = i;
    }

    // No pair found
    cout << "IMPOSSIBLE\n";
    return 0;
}

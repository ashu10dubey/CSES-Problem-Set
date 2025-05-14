#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

long long min_diff = LLONG_MAX;

void find_min_diff(vector<int> &weights, int i, long long group1, long long group2) {
    if (i == weights.size()) {
        min_diff = min(min_diff, abs(group1 - group2));
        return;
    }

    // Option 1: Include the current apple in group 1
    find_min_diff(weights, i + 1, group1 + weights[i], group2);
    
    // Option 2: Include the current apple in group 2
    find_min_diff(weights, i + 1, group1, group2 + weights[i]);
}

int main() {
    FAST_IO;
    int n;
    cin >> n;
    vector<int> weights(n);
    for (int &w : weights) cin >> w;

    // Start the recursive division process
    find_min_diff(weights, 0, 0, 0);

    cout << min_diff << "\n";
    return 0;
}

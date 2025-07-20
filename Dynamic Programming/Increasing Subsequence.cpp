#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n), dp;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int x : arr) {
        // Find the first element in dp >= x
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) {
            // x extends the LIS
            dp.push_back(x);
        } else {
            // x could improve a shorter subsequence
            *it = x;
        }
    }

    cout << dp.size() << "\n";
    return 0;
}

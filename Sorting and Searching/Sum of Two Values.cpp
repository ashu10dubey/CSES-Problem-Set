#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time Complexity: O(n log n)
// Space Complexity: O(n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;

    vector<pair<long long, int>> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first;
        arr[i].second = i + 1; // 1-based indexing
    }

    sort(arr.begin(), arr.end());

    int left = 0, right = n - 1;
    while (left < right) {
        long long sum = arr[left].first + arr[right].first;
        if (sum == x) {
            cout << arr[left].second << " " << arr[right].second << '\n';
            return 0;
        } else if (sum < x) {
            ++left;
        } else {
            --right;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}

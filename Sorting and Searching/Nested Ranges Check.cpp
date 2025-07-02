#include <bits/stdc++.h>
using namespace std;

struct Range {
    int x, y, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Range> ranges(n);

    for (int i = 0; i < n; ++i) {
        cin >> ranges[i].x >> ranges[i].y;
        ranges[i].idx = i;
    }

    // Result vectors
    vector<int> contains(n, 0);
    vector<int> contained(n, 0);

    // ----------- CHECK CONTAINS ----------------
    // Sort by start ascending, end descending
    sort(ranges.begin(), ranges.end(), [](const Range &a, const Range &b) {
        if (a.x == b.x) return a.y > b.y;
        return a.x < b.x;
    });

    // Process in reverse to track how many ranges have smaller y values
    map<int, int> y_count;
    for (int i = n - 1; i >= 0; --i) {
        auto &[x, y, idx] = ranges[i];
        // If same y already exists => this one contains a previous one
        if (y_count.count(y)) contains[idx] = 1;
        y_count[y]++;
    }

    // ----------- CHECK CONTAINED BY ----------------
    // Sort by start ascending, end ascending
    sort(ranges.begin(), ranges.end(), [](const Range &a, const Range &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });

    y_count.clear();
    for (int i = 0; i < n; ++i) {
        auto &[x, y, idx] = ranges[i];
        if (y_count.lower_bound(y) != y_count.end()) contained[idx] = 1;
        y_count[y]++;
    }

    // Output
    for (int i = 0; i < n; ++i) cout << contains[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) cout << contained[i] << " ";
    cout << "\n";

    return 0;
}

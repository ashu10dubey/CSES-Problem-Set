#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].first >> movies[i].second;
    }

    // Sort by movie end times
    sort(movies.begin(), movies.end(), [](auto &a, auto &b) {
        return a.second < b.second;
    });

    multiset<int> endTimes;  // when each member is free
    for (int i = 0; i < k; ++i) {
        endTimes.insert(0); // all k members are initially free at time 0
    }

    int count = 0;
    for (auto &[start, end] : movies) {
        auto it = endTimes.upper_bound(start);
        if (it == endTimes.begin()) continue; // no member is free before start
        --it; // best match: latest time <= start
        endTimes.erase(it); // assign this member
        endTimes.insert(end); // now this member is busy until 'end'
        count++;
    }

    cout << count << endl;
    return 0;
}

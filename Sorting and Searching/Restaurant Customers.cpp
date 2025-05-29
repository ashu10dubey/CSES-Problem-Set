#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> events; // Pair: <time, type>, type = +1 (arrival), -1 (departure)

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(a, 1);  // Arrival: +1
        events.emplace_back(b, -1); // Departure: -1
    }

    // Sort events by time. If same time, departures (-1) go before arrivals (+1)
    sort(events.begin(), events.end());

    int curr_customers = 0, max_customers = 0;

    for (auto [time, type] : events) {
        curr_customers += type;
        max_customers = max(max_customers, curr_customers);
    }

    cout << max_customers << '\n';
    return 0;
}

/*
-------------------------------------------------------
 Time Complexity:
- Reading n pairs: O(n)
- Sorting 2n events: O(n log n)
- Iterating 2n events: O(n)
- Total: O(n log n)

 Space Complexity:
- O(n) for storing events
-------------------------------------------------------
*/

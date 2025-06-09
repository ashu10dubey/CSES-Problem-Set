#include <iostream>
#include <set>
#include <map>
using namespace std;

/*
Time Complexity:
- Each insertion and update takes O(log n) due to set/map.
- Total time: O(n log n), where n is the number of traffic lights.

Space Complexity: O(n) to store positions and segment lengths.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n;
    cin >> x >> n;

    set<int> positions;         // Stores all traffic light positions
    multiset<int> segments;     // Stores all segment lengths between lights

    positions.insert(0);
    positions.insert(x);
    segments.insert(x); // Initially, one big segment from 0 to x

    for (int i = 0; i < n; ++i) {
        int pos;
        cin >> pos;

        // Find neighbors of the new traffic light
        auto it = positions.upper_bound(pos);
        int right = *it;
        int left = *prev(it);

        // Remove old segment between left and right
        segments.erase(segments.find(right - left));

        // Add two new segments
        segments.insert(pos - left);
        segments.insert(right - pos);

        // Insert the new traffic light
        positions.insert(pos);

        // Output the current max segment length
        cout << *segments.rbegin() << " ";
    }

    cout << "\n";
    return 0;
}

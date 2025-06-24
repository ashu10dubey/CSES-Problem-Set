#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<tuple<int, int, int>> customers(n); // {arrival, departure, index}
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        customers[i] = {a, b, i};
    }

    sort(customers.begin(), customers.end());

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // {end_time, room_id}
    vector<int> room_assignments(n);
    int room_count = 0;

    for (auto &[start, end, idx] : customers) {
        if (!pq.empty() && pq.top().first < start) {
            // Reuse room
            auto [prev_end, room_id] = pq.top(); pq.pop();
            room_assignments[idx] = room_id;
            pq.push({end, room_id});
        } else {
            // Allocate new room
            ++room_count;
            room_assignments[idx] = room_count;
            pq.push({end, room_count});
        }
    }

    cout << room_count << "\n";
    for (int r : room_assignments) cout << r << " ";
    cout << "\n";

    return 0;
}

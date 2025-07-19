#include <bits/stdc++.h>
using namespace std;

// Custom type to store intervals and their original index
typedef array<int, 3> triple;

// Constants for max size
const int maxN = 2e5 + 1;
const int SIZE = 2 * maxN; // Needed for BIT (Fenwick Tree)

int N;                         // Number of intervals
int ans[2][maxN];              // ans[0][i]: ranges it contains, ans[1][i]: ranges that contain it
int ds[SIZE];                  // Fenwick Tree array for efficient prefix sums
triple intervals[maxN];        // Store all intervals with original indices
set<int> unique_vals;          // Store all unique x and y values (for compression)
map<int, int> mp;              // Map original x/y to compressed values

// BIT update: add 'val' to index 'idx'
void update(int idx, int val) {
    for (int i = idx; i < SIZE; i += i & -i)
        ds[i] += val;
}

// BIT query: prefix sum from 1 to idx
int query(int idx) {
    int cnt = 0;
    for (int i = idx; i > 0; i -= i & -i)
        cnt += ds[i];
    return cnt;
}

int main() {
    scanf("%d", &N); // Read number of intervals

    // Read all intervals and prepare coordinate compression
    for (int i = 0, x, y; i < N; i++) {
        scanf("%d %d", &x, &y);
        intervals[i] = {x, y, i}; // Store interval with original index
        unique_vals.insert(x);
        unique_vals.insert(y);   // Add to compression set
    }

    // Sort by x ascending, and y descending (so longer intervals come first when x is same)
    sort(intervals, intervals + N, [](triple A, triple B) {
        return (A[0] == B[0] ? A[1] > B[1] : A[0] < B[0]);
    });

    // Coordinate compression
    int val_id = 1;
    for (int x : unique_vals)
        mp[x] = val_id++;

    // PASS 1: Calculate how many intervals each interval contains
    // Traverse from end → start to ensure inner intervals are seen later
    for (int i = N - 1; i >= 0; i--) {
        int y = mp[intervals[i][1]];     // Compressed y
        int id = intervals[i][2];        // Original index

        ans[0][id] = query(y);           // Count how many intervals with y ≤ current y
        update(y, 1);                    // Mark current interval's end in BIT
    }

    // Reset Fenwick Tree
    fill(ds, ds + SIZE, 0);

    // PASS 2: Calculate how many intervals contain each interval
    // Traverse from start → end
    for (int i = 0; i < N; i++) {
        int y = mp[intervals[i][1]];     // Compressed y
        int id = intervals[i][2];        // Original index

        ans[1][id] = i - query(y - 1);   // i = how many seen so far, subtract those that can't contain current
        update(y, 1);                    // Mark this interval's end in BIT
    }

    // Output the results
    // Line 1: how many intervals each interval contains
    for (int j = 0; j < N; j++)
        printf("%d%c", ans[0][j], " \n"[j == N - 1]);

    // Line 2: how many intervals contain each interval
    for (int j = 0; j < N; j++)
        printf("%d%c", ans[1][j], " \n"[j == N - 1]);
}

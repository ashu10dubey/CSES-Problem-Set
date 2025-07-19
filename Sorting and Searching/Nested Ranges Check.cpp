#include <bits/stdc++.h>
using namespace std;

// Each interval will be stored as a triple: {x, y, index}
typedef array<int, 3> triple;

const int maxN = 2e5 + 1;     // Maximum number of intervals
const int SIZE = 2 * maxN;    // BIT size after coordinate compression

int N;                         // Number of intervals
int ans[2][maxN];              // ans[0][i]: contains other, ans[1][i]: is contained
int ds[SIZE];                  // Fenwick Tree (Binary Indexed Tree) array
triple intervals[maxN];        // Store all intervals
set<int> unique_vals;          // For coordinate compression (store all unique x and y)
map<int, int> mp;              // Map original x/y to compressed values

// Update BIT: add 'val' at index 'idx'
void update(int idx, int val) {
    for (int i = idx; i < SIZE; i += i & -i)  // Increment all affected BIT nodes
        ds[i] += val;
}

// Query BIT: get prefix sum from 1 to idx
int query(int idx) {
    int cnt = 0;
    for (int i = idx; i > 0; i -= i & -i)     // Climb down the BIT tree
        cnt += ds[i];
    return cnt;
}

int main() {
    // Read number of intervals
    scanf("%d", &N);

    // Read each interval and prepare for compression
    for (int i = 0, x, y; i < N; i++) {
        scanf("%d %d", &x, &y);
        intervals[i] = {x, y, i};     // Store x, y, and original index
        unique_vals.insert(x);       // Add to compression set
        unique_vals.insert(y);
    }

    // Sort intervals by x increasing, and y decreasing (important for proper nesting)
    sort(intervals, intervals + N, [](triple A, triple B) {
        return (A[0] == B[0] ? A[1] > B[1] : A[0] < B[0]);
    });

    // Compress coordinates: assign 1..2*N to all unique x/y
    int val_id = 1;
    for (int x : unique_vals)
        mp[x] = val_id++;

    // Pass 1: Count how many intervals each interval contains
    // Traverse from right to left
    for (int i = N - 1; i >= 0; i--) {
        int y = mp[intervals[i][1]];     // Compressed y-coordinate
        int id = intervals[i][2];        // Original index

        ans[0][id] = query(y);           // Query: how many intervals seen so far end ≤ y
        update(y, 1);                    // Mark current interval as seen
    }

    // Clear BIT for reuse
    fill(ds, ds + SIZE, 0);

    // Pass 2: Count how many intervals contain each interval
    // Traverse from left to right
    for (int i = 0; i < N; i++) {
        int y = mp[intervals[i][1]];     // Compressed y
        int id = intervals[i][2];        // Original index

        ans[1][id] = i - query(y - 1);   // i = # of processed intervals
                                         // query(y-1) = # of intervals that cannot contain this one
        update(y, 1);                    // Mark this interval as processed
    }

    // Output the answers
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < N; j++)
            printf("%d%c", (ans[i][j] ? 1 : 0), (" \n")[j == N - 1]);
}

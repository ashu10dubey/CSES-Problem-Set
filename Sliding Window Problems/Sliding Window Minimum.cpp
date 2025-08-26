#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    int k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    // Generate the array
    vector<long long> arr(n);
    arr[0] = x;
    for (int i = 1; i < n; ++i) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }

    deque<int> dq; // Deque to store indices
    long long xor_sum = 0;

    for (int i = 0; i < n; ++i) {
        // 1. Remove out-of-window elements from the front
        // The window is [i-k+1, i]. Indices < i-k+1 are old.
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // 2. Remove useless elements from the back
        // If arr[i] is smaller, elements at the back are no longer candidates
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }

        // 3. Add the current element's index to the back
        dq.push_back(i);

        // 4. If the window is fully formed, get the minimum
        // The minimum is at the front of the deque
        if (i >= k - 1) {
            if (xor_sum == 0 && i == k - 1) { // First window
                xor_sum = arr[dq.front()];
            } else {
                xor_sum ^= arr[dq.front()];
            }
        }
    }

    cout << xor_sum << endl;

    return 0;
}
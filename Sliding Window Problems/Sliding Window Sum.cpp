#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    // 1. Generate the array
    vector<long long> arr(n);
    arr[0] = x;
    for (int i = 1; i < n; ++i) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }

    // 2. Calculate the sum of the first window
    long long current_sum = 0;
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }

    // Initialize the XOR sum with the sum of the first window
    long long xor_sum = current_sum;

    // 3. Slide the window from the k-th element to the end
    for (int i = k; i < n; ++i) {
        // Update sum in O(1): Add the new element, subtract the old one
        long long outgoing_element = arr[i - k];
        long long incoming_element = arr[i];
        current_sum = current_sum - outgoing_element + incoming_element;

        // Update the total XOR sum
        xor_sum ^= current_sum;
    }

    cout << xor_sum << endl;

    return 0;
}
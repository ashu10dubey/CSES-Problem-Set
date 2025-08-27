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

    // 2. Calculate the XOR sum of the first window
    long long current_xor = 0;
    for (int i = 0; i < k; ++i) {
        current_xor ^= arr[i];
    }

    // Initialize the final answer with the XOR sum of the first window
    long long xor_of_xors = current_xor;

    // 3. Slide the window from the k-th element to the end
    for (int i = k; i < n; ++i) {
        // Update XOR sum in O(1): XOR with the outgoing and incoming elements
        long long outgoing_element = arr[i - k];
        long long incoming_element = arr[i];
        current_xor ^= outgoing_element ^ incoming_element;

        // Update the final answer
        xor_of_xors ^= current_xor;
    }

    cout << xor_of_xors << endl;

    return 0;
}
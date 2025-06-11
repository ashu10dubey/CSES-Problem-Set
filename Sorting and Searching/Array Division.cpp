#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_valid(const vector<long long> &a, long long max_sum, int k) {
    long long current_sum = 0;
    int count = 1;

    for (long long num : a) {
        if (current_sum + num > max_sum) {
            count++;
            current_sum = num;
        } else {
            current_sum += num;
        }
    }
    return count <= k;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    long long lo = *max_element(a.begin(), a.end());
    long long hi = 0;
    for (auto x : a) hi += x;

    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (is_valid(a, mid, k)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << endl;
    return 0;
}

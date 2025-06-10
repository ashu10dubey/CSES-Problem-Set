#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;

    unordered_map<int, int> freq;
    long long res = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        freq[arr[right]]++;
        // Move left pointer to keep window distinct
        while (freq[arr[right]] > 1) {
            freq[arr[left]]--;
            left++;
        }
        // All subarrays ending at right and starting from left to right are valid
        res += (right - left + 1);
    }

    cout << res << endl;
    return 0;
}

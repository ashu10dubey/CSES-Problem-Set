#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    unordered_map<int, int> freq;
    long long result = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        freq[a[right]]++;

        while (freq.size() > k) {
            freq[a[left]]--;
            if (freq[a[left]] == 0)
                freq.erase(a[left]);
            left++;
        }

        result += (right - left + 1);
    }

    cout << result << "\n";
    return 0;
}

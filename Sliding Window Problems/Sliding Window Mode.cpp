#include <bits/stdc++.h>
using namespace std;

map<int, int> freqs;
map<int, set<int>> counts;

void add(int x) {
    if (freqs.count(x)) {
        // Remove from old frequency group
        counts[freqs[x]].erase(x);
        if (counts[freqs[x]].empty()) {
            counts.erase(freqs[x]);
        }
    }
    // Increment frequency
    freqs[x]++;
    // Add to new frequency group
    counts[freqs[x]].insert(x);
}

void remove(int x) {
    // Remove from old frequency group
    counts[freqs[x]].erase(x);
    if (counts[freqs[x]].empty()) {
        counts.erase(freqs[x]);
    }
    // Decrement frequency
    freqs[x]--;
    // Add to new frequency group if it still exists
    if (freqs[x] > 0) {
        counts[freqs[x]].insert(x);
    } else {
        freqs.erase(x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Process first window
    for (int i = 0; i < k; ++i) {
        add(arr[i]);
    }
    
    // The highest frequency is the last key in the ordered map 'counts'
    // The mode is the first element in the set for that frequency
    cout << *counts.rbegin()->second.begin();

    // Slide the window
    for (int i = k; i < n; ++i) {
        remove(arr[i - k]);
        add(arr[i]);
        cout << " " << *counts.rbegin()->second.begin();
    }
    cout << endl;

    return 0;
}
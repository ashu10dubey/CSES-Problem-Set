#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    map<int, int> freq_map;

    // Process the first window
    for (int i = 0; i < k; ++i) {
        freq_map[arr[i]]++;
    }
    cout << freq_map.size();

    // Slide the window for the rest of the array
    for (int i = k; i < n; ++i) {
        // 1. Add the incoming element
        int incoming = arr[i];
        freq_map[incoming]++;

        // 2. Remove the outgoing element
        int outgoing = arr[i - k];
        freq_map[outgoing]--;
        
        // 3. If an element's count becomes 0, erase it from the map
        if (freq_map[outgoing] == 0) {
            freq_map.erase(outgoing);
        }

        cout << " " << freq_map.size();
    }
    cout << endl;

    return 0;
}
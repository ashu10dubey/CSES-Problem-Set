#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Time Complexity: O(n)
    - Each song is processed at most twice: once when right pointer moves, once when left pointer advances.
Space Complexity: O(n)
    - Hash map stores at most n entries (song IDs).
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> songs(n);
    for (int i = 0; i < n; ++i) {
        cin >> songs[i];
    }

    unordered_map<int, int> last_occurrence; // maps song ID to its latest index
    int left = 0, max_len = 0;

    for (int right = 0; right < n; ++right) {
        int song = songs[right];

        // If song already seen and its last occurrence is within current window
        if (last_occurrence.count(song) && last_occurrence[song] >= left) {
            // Move left just beyond last occurrence
            left = last_occurrence[song] + 1;
        }

        // Update last occurrence of the current song
        last_occurrence[song] = right;

        // Update the max length of the window
        max_len = max(max_len, right - left + 1);
    }

    cout << max_len << "\n";
    return 0;
}

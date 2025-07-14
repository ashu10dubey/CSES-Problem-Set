#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Time Complexity: O(n)
 - Each element is inserted and removed from the hash map at most once.
 - Both pointers (left, right) move forward at most n times.
Space Complexity: O(n)
 - At most n unique song IDs stored in the map.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> k(n);
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    unordered_map<int, int> freq; // Store frequency of song ids in current window
    int left = 0, max_len = 0;

    for (int right = 0; right < n; ++right) {
        freq[k[right]]++;

        // If we see a duplicate, shrink window from left until all elements are unique
        while (freq[k[right]] > 1) {
            freq[k[left]]--;
            left++;
        }

        // Update maximum unique window size
        max_len = max(max_len, right - left + 1);
    }

    cout << max_len << '\n';
    return 0;
}

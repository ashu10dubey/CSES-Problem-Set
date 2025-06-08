#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*
Time Complexity: O(n * log n)
 - For each cube, we perform a binary search or insertion/removal in a multiset.
Space Complexity: O(n)
 - In the worst case, all cubes form separate towers.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    multiset<int> towers;

    for (int i = 0; i < n; ++i) {
        int cube;
        cin >> cube;

        // Find the first tower whose top is strictly greater than cube
        auto it = towers.upper_bound(cube);

        if (it != towers.end()) {
            towers.erase(it); // Place cube on top (replace tower top)
        }

        towers.insert(cube); // Create new tower or update existing one
    }

    cout << towers.size() << "\n"; // Total towers formed
    return 0;
}

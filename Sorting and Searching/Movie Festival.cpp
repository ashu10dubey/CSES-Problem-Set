#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Store movies as pairs of (end time, start time) for sorting by end time
    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        movies[i] = {b, a}; // end, start
    }

    // Sort movies by end time (greedy strategy)
    sort(movies.begin(), movies.end());

    int count = 0;         // Maximum movies we can watch
    int last_end = 0;      // End time of the last selected movie

    for (const auto& [end, start] : movies) {
        if (start >= last_end) {
            ++count;       // Select this movie
            last_end = end;
        }
    }

    cout << count << '\n';
    return 0;
}

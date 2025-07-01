#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int main() {
    int n;
    cin >> n;
    vector<pll> tasks(n); // (duration, deadline)

    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].first >> tasks[i].second;
    }

    // Sort tasks by duration (greedy strategy)
    sort(tasks.begin(), tasks.end());

    ll time = 0, total_reward = 0;
    for (const auto& [duration, deadline] : tasks) {
        time += duration;
        total_reward += deadline - time;
    }

    cout << total_reward << "\n";
    return 0;
}

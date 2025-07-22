#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef array<ll, 3> Project;

int main() {
    int n;
    cin >> n;
    vector<Project> projects(n);
    
    for (int i = 0; i < n; ++i) {
        ll a, b, p;
        cin >> a >> b >> p;
        projects[i] = {b, a, p}; // sort by end day
    }

    sort(projects.begin(), projects.end());

    // Store pairs of (end_time, max_reward_till_end)
    vector<pair<ll, ll>> dp = {{0, 0}};  // (end_day, max_profit)

    for (auto [end, start, profit] : projects) {
        // Binary search for the latest project that ends before 'start'
        auto it = upper_bound(dp.begin(), dp.end(), make_pair(start - 1, LLONG_MAX));
        --it;
        ll current = it->second + profit;
        if (current > dp.back().second) {
            dp.emplace_back(end, current);
        }
    }

    cout << dp.back().second << '\n';
    return 0;
}

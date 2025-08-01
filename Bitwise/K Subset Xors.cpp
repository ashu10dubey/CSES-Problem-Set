#include <bits/stdc++.h>
using namespace std;

// Build basis for XOR space
vector<long long> build_basis(vector<long long> &arr) {
    vector<long long> basis;
    for (long long x : arr) {
        for (auto b : basis)
            x = min(x, x ^ b);
        if (x)
            basis.push_back(x);
    }
    sort(basis.begin(), basis.end());
    return basis;
}

struct State {
    long long val;
    int idx;
    vector<int> mask;
    bool operator>(const State &other) const { return val > other.val; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<long long> arr(n);
    for (auto &x : arr) cin >> x;

    vector<long long> basis = build_basis(arr);
    int m = (int)basis.size();

    // Min-heap for next minimum XORs
    using pli = pair<long long, vector<int>>;
    priority_queue<pair<long long, vector<int>>, vector<pair<long long, vector<int>>>, greater<>> pq;
    set<vector<int>> vis;

    vector<long long> result;

    // Initial state: 0 (empty set), mask all zeroes
    pq.push({0LL, vector<int>(m, 0)});
    vis.insert(vector<int>(m, 0));

    while ((int)result.size() < k && !pq.empty()) {
        auto [cur, mask] = pq.top(); pq.pop();
        result.push_back(cur);

        // Generate neighbors by flipping one bit in the mask from 0 to 1
        for (int i = 0; i < m; ++i) {
            if (mask[i] == 0) {
                vector<int> nmask = mask;
                nmask[i] = 1;
                if (vis.count(nmask)) continue;
                long long nval = cur ^ basis[i];
                pq.push({nval, nmask});
                vis.insert(nmask);
            }
        }
    }

    // If basis is empty (all zeros), print 0 k times
    if (basis.empty()) {
        for (int i = 0; i < k; ++i) cout << "0 ";
        cout << endl;
        return 0;
    }
    for (long long x : result) cout << x << ' ';
    cout << endl;
}

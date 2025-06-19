#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + arr[i - 1];
    }

    deque<int> dq;
    long long ans = LLONG_MIN;

    for (int j = a; j <= n; j++) {
        int new_index = j - a;

        while (!dq.empty() && pre[dq.back()] >= pre[new_index]) {
            dq.pop_back();
        }
        dq.push_back(new_index);

        while (!dq.empty() && dq.front() < j - b) {
            dq.pop_front();
        }

        if (!dq.empty()) {
            long long candidate = pre[j] - pre[dq.front()];
            if (candidate > ans) {
                ans = candidate;
            }
        }
    }

    cout << ans << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

// Custom hash for unordered_map to avoid collisions
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    unordered_map<long long, int, custom_hash> last;
    int ans = 0, l = 0;
    for (int r = 0; r < n; ++r) {
        if (last.count(a[r]) && last[a[r]] >= l) {
            l = last[a[r]] + 1;
        }
        last[a[r]] = r;
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
}

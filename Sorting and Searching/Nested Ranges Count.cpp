#include <bits/stdc++.h>
using namespace std;

struct Range {
    int x, y, idx;
};

struct BIT {
    vector<int> bit;
    int n;
    BIT(int n) : n(n), bit(n + 2) {}
    void add(int i, int v) {
        for (; i <= n; i += i & -i) bit[i] += v;
    }
    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
    int range(int l, int r) { return sum(r) - sum(l - 1); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<Range> ranges(n);
    vector<int> coords;
    for (int i = 0; i < n; ++i) {
        cin >> ranges[i].x >> ranges[i].y;
        ranges[i].idx = i;
        coords.push_back(ranges[i].x);
        coords.push_back(ranges[i].y);
    }
    // Coordinate compression
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto get = [&](int v) {
        return lower_bound(coords.begin(), coords.end(), v) - coords.begin() + 1;
    };
    for (auto& r : ranges) {
        r.x = get(r.x);
        r.y = get(r.y);
    }
    // For "contains"
    vector<int> contains(n), contained_by(n);
    {
        auto v = ranges;
        sort(v.begin(), v.end(), [](auto a, auto b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y > b.y;
        });
        BIT bit(coords.size() + 2);
        for (int i = 0; i < n; ++i) {
            // Count how many ranges have y <= current y (already processed)
            contains[v[i].idx] = bit.sum(v[i].y);
            bit.add(v[i].y, 1);
        }
        // Remove self-counting
        for (int i = 0; i < n; ++i) contains[i]--;
    }
    // For "contained by"
    {
        auto v = ranges;
        sort(v.begin(), v.end(), [](auto a, auto b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });
        BIT bit(coords.size() + 2);
        for (int i = n - 1; i >= 0; --i) {
            contained_by[v[i].idx] = bit.sum(coords.size() + 1) - bit.sum(v[i].y - 1);
            bit.add(v[i].y, 1);
        }
        // Remove self-counting
        for (int i = 0; i < n; ++i) contained_by[i]--;
    }
    for (int i = 0; i < n; ++i) cout << contains[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) cout << contained_by[i] << " ";
    cout << "\n";
}

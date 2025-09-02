#include <bits/stdc++.h>
using namespace std;

struct SlidingMedian {
    multiset<long long> left, right;
    long long sumLeft = 0, sumRight = 0;

    void balance() {
        if (left.size() > right.size() + 1) {
            auto it = prev(left.end());
            sumLeft -= *it;
            sumRight += *it;
            right.insert(*it);
            left.erase(it);
        } else if (right.size() > left.size()) {
            auto it = right.begin();
            sumRight -= *it;
            sumLeft += *it;
            left.insert(*it);
            right.erase(it);
        }
    }

    void insert(long long x) {
        if (left.empty() || x <= *prev(left.end())) {
            left.insert(x);
            sumLeft += x;
        } else {
            right.insert(x);
            sumRight += x;
        }
        balance();
    }

    void erase(long long x) {
        if (left.find(x) != left.end()) {
            left.erase(left.find(x));
            sumLeft -= x;
        } else {
            right.erase(right.find(x));
            sumRight -= x;
        }
        balance();
    }

    long long getCost() {
        long long median = *prev(left.end());
        long long cost = median * (long long)left.size() - sumLeft
                       + sumRight - median * (long long)right.size();
        return cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    SlidingMedian sm;
    for (int i = 0; i < k; i++) sm.insert(a[i]);
    cout << sm.getCost();

    for (int i = k; i < n; i++) {
        sm.erase(a[i-k]);
        sm.insert(a[i]);
        cout << " " << sm.getCost();
    }
    cout << "\n";

    return 0;
}

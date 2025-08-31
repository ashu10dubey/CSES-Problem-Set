#include <bits/stdc++.h>
using namespace std;

multiset<int> lower, upper;

void balance() {
    while (lower.size() > upper.size() + 1) {
        upper.insert(*lower.rbegin());
        lower.erase(prev(lower.end()));
    }
    while (upper.size() > lower.size()) {
        lower.insert(*upper.begin());
        upper.erase(upper.begin());
    }
}

void add(int val) {
    if (!lower.empty() && val <= *lower.rbegin()) {
        lower.insert(val);
    } else {
        upper.insert(val);
    }
    balance();
}

void remove(int val) {
    if (upper.count(val)) {
        upper.erase(upper.find(val));
    } else {
        lower.erase(lower.find(val));
    }
    balance();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Process first window
    for (int i = 0; i < k; ++i) {
        add(a[i]);
    }
    
    cout << *lower.rbegin();

    // Slide the window
    for (int i = k; i < n; ++i) {
        remove(a[i - k]);
        add(a[i]);
        cout << " " << *lower.rbegin();
    }
    cout << endl;

    return 0;
}
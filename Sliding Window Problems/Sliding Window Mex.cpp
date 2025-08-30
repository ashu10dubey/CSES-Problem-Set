#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> freq(k + 2, 0);
    set<int> missing;
    for (int i = 0; i <= k; i++) missing.insert(i);

    for (int i = 0; i < k; i++) {
        if (a[i] <= k) {
            if (freq[a[i]] == 0) missing.erase(a[i]);
            freq[a[i]]++;
        }
    }

    cout << *missing.begin();
    for (int i = k; i < n; i++) {
        int out = a[i - k];
        if (out <= k) {
            freq[out]--;
            if (freq[out] == 0) missing.insert(out);
        }
        int in = a[i];
        if (in <= k) {
            if (freq[in] == 0) missing.erase(in);
            freq[in]++;
        }
        cout << " " << *missing.begin();
    }
    cout << "\n";
}

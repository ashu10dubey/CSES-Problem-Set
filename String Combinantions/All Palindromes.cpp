#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if(!(cin >> s)) return 0;
    int n = (int)s.size();

    vector<int> d1(n);
    {
        int l = 0, r = -1;
        for (int i = 0; i < n; i++) {
            int k = 1;
            if (i <= r) k = min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k;
            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }
    }

    vector<int> d2(n);
    {
        int l = 0, r = -1;
        for (int i = 0; i < n; i++) {
            int k = 0;
            if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    vector<int> ans(n, 1);
    for (int c = 0; c < n; c++) {
        int k = d1[c];
        int end = c + (k - 1);
        int len = 2 * k - 1;
        if (end >= 0 && end < n)
            ans[end] = max(ans[end], len);
    }
    for (int c = 0; c < n; c++) {
        int k = d2[c];
        if (k == 0) continue;
        int end = c + k - 1;
        int len = 2 * k;
        if (end >= 0 && end < n)
            ans[end] = max(ans[end], len);
    }

    for (int r = n - 1; r - 1 >= 0; r--) {
        ans[r - 1] = max(ans[r - 1], max(1, ans[r] - 2));
    }

    for (int i = 0; i < n; i++) {
        ans[i] = min(ans[i], i + 1);
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}

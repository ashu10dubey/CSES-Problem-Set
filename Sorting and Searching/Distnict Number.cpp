#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<int> distinct;  // Red-Black tree (O(log n) insert but consistent performance)

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        distinct.insert(x);
    }

    cout << distinct.size() << '\n';
    return 0;
}

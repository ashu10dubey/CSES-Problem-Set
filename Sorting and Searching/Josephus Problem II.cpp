#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    ordered_set children;
    for (int i = 1; i <= n; ++i) {
        children.insert(i);
    }

    vector<int> result;
    long long pos = 0;

    while (!children.empty()) {
        int sz = children.size();
        pos = (pos + k) % sz;
        auto it = children.find_by_order(pos);
        result.push_back(*it);
        children.erase(it);
    }

    for (int i = 0; i < result.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << result[i];
    }
    cout << "\n";

    return 0;
}

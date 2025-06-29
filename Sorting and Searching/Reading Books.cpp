#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> t(n);
    long long total = 0, max_time = 0;

    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        total += t[i];
        max_time = max(max_time, t[i]);
    }

    cout << max(total, 2 * max_time) << '\n';
    return 0;
}

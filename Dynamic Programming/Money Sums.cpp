#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> coins(n);
    for (int& x : coins) cin >> x;

    const int MAX_SUM = 100000;
    bitset<MAX_SUM + 1> dp;
    dp[0] = 1;

    for (int c : coins) {
        dp |= (dp << c); // Shift by coin value, OR it to simulate inclusion
    }

    vector<int> result;
    for (int sum = 1; sum <= MAX_SUM; ++sum) {
        if (dp[sum]) result.push_back(sum);
    }

    cout << result.size() << "\n";
    for (int sum : result) cout << sum << " ";
    cout << "\n";
    return 0;
}

// 🚀 Competitive Programming Boilerplate for Fast I/O and Clean Code
#include <bits/stdc++.h>
using namespace std;

// 🌐 Speed up I/O
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

// 🔥 Common Shortcuts
#define int long long         // Use long long for all integers by default
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(x) (int)(x).size()
#define F first
#define S second
#define endl '\n'

// 📊 Constants
const int INF = 1e18;
const int MOD = 1e9 + 7;

// 🌐 Main Solver Function
void solve() {
    int n;
    cin >> n;
    
    // 🔄 Check if partition is possible
    int sum = n * (n + 1) / 2;
    if (sum % 2 != 0) {
        cout << "NO" << endl;
        return;
    }

    // ✅ Partition is possible
    cout << "YES" << endl;
    int halfSum = sum / 2;
    vector<int> set1, set2;

    // 🌐 Greedy Partitioning
    for (int i = n; i >= 1; --i) {
        if (halfSum - i >= 0) {
            set1.pb(i);
            halfSum -= i;
        } else {
            set2.pb(i);
        }
    }

    // 📝 Print the results
    cout << sz(set1) << endl;
    for (int num : set1) cout << num << " ";
    cout << endl;
    
    cout << sz(set2) << endl;
    for (int num : set2) cout << num << " ";
    cout << endl;
}

// 🚀 Main Function
int32_t main() {
    FAST_IO;
    int t = 1;
    // cin >> t;  // Uncomment if multiple test cases
    while (t--) solve();
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    
    if (a + b > n || a < 0 || b < 0) {
        cout << "NO\n";
        return;
    }
    int t = n - a - b;
    if (t < 0) {
        cout << "NO\n";
        return;
    }
    
    vector<int> a_tie, b_tie;
    for (int i = 1; i <= t; ++i) {
        a_tie.push_back(i);
        b_tie.push_back(i);
    }
    
    vector<int> s;
    for (int i = t + 1; i <= n; ++i) {
        s.push_back(i);
    }
    
    vector<int> a_non_tie;
    vector<int> b_non_tie;
    
    a_non_tie.insert(a_non_tie.end(), s.end() - a, s.end());
    a_non_tie.insert(a_non_tie.end(), s.begin(), s.begin() + b);
    
    b_non_tie.insert(b_non_tie.end(), s.begin(), s.begin() + a);
    b_non_tie.insert(b_non_tie.end(), s.end() - b, s.end());
    
    vector<int> a_full = a_tie;
    a_full.insert(a_full.end(), a_non_tie.begin(), a_non_tie.end());
    
    vector<int> b_full = b_tie;
    b_full.insert(b_full.end(), b_non_tie.begin(), b_non_tie.end());
    
    int count_a = 0, count_b = 0;
    for (int i = 0; i < n; ++i) {
        if (a_full[i] > b_full[i]) count_a++;
        else if (a_full[i] < b_full[i]) count_b++;
    }
    
    if (count_a == a && count_b == b) {
        cout << "YES\n";
        for (int x : a_full) cout << x << " ";
        cout << "\n";
        for (int x : b_full) cout << x << " ";
        cout << "\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

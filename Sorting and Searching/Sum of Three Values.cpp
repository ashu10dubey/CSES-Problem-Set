#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    if (n < 3) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1; // Store 1-based index
    }
    
    sort(a.begin(), a.end());
    
    for (int i = 0; i <= n - 3; ++i) {
        long long target = x - a[i].first;
        int left = i + 1, right = n - 1;
        
        while (left < right) {
            long long current_sum = a[left].first + a[right].first;
            
            if (current_sum == target) {
                cout << a[i].second << " " << a[left].second << " " << a[right].second << endl;
                return 0;
            } else if (current_sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }
    
    cout << "IMPOSSIBLE" << endl;
    return 0;
}

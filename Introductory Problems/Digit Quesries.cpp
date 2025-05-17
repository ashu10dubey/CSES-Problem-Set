#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        
        // Find the length of the number containing the k-th digit
        ll length = 1, count = 9, base = 1;
        while (k > length * count) {
            k -= length * count;
            length++;
            count *= 10;
            base *= 10;
        }

        // Find the actual number
        ll number = base + (k - 1) / length;
        string num_str = to_string(number);
        
        // Print the correct digit
        cout << num_str[(k - 1) % length] << "\n";
    }

    return 0;
}

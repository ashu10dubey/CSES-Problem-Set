#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    unordered_map<int, long long> modCount;
    long long sum = 0, res = 0;

    modCount[0] = 1;  // to count subarrays starting from index 0

    for (int i = 0; i < n; ++i) {
        sum += a[i];
        int mod = ((sum % n) + n) % n;  // handle negative mods
        res += modCount[mod];
        modCount[mod]++;
    }

    cout << res << endl;
    return 0;
}

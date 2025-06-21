#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto &val : a) cin >> val;

    unordered_map<long long, int> prefix_count;
    prefix_count[0] = 1; // empty prefix

    long long sum = 0, result = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        if (prefix_count.count(sum - x))
            result += prefix_count[sum - x];
        prefix_count[sum]++;
    }

    cout << result << "\n";
    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<long long> arr(n);
    unordered_map<long long, int> freqMap;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        freqMap[arr[i]]++;
    }

    long long result = 1;
    for (auto& kv : freqMap) {
        int count = kv.second;
        result = (result * (count + 1)) % MOD;
    }

    result = (result - 1 + MOD) % MOD;
    cout << result << endl;

    return 0;
}

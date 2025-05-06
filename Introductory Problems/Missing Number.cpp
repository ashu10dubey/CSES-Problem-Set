#include <iostream>
using namespace std;

int main() {
    long long n, x, sum = 0;
    cin >> n;

    // Read n-1 numbers and accumulate their sum
    for (int i = 1; i < n; ++i) {
        cin >> x;
        sum += x;
    }

    // Calculate expected sum from 1 to n
    long long total = n * (n + 1) / 2;

    // Output the missing number
    cout << total - sum << endl;
    return 0;
}

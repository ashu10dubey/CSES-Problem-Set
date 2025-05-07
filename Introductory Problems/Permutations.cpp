#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Special case where no solution exists
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    // Print evens first
    for (int i = 2; i <= n; i += 2) {
        cout << i << " ";
    }

    // Print odds next
    for (int i = 1; i <= n; i += 2) {
        cout << i << " ";
    }

    cout << "\n";
    return 0;
}

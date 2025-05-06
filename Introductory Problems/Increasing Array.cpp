#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long move = 0, maxtill = 0;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        if (x < maxtill) {
            move += (maxtill - x);
        } else {
            maxtill = x;
        }
    }

    cout << move << "\n";
    return 0;
}
/*
| Time   | O(n)  |
| Space  | O(1)  |
*/

#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

void solve(int n, int src, int dest, int aux) {
    if (n == 0) return;
    solve(n - 1, src, aux, dest); // Move n-1 disks to auxiliary
    cout << src << " " << dest << "\n"; // Move nth disk to destination
    solve(n - 1, aux, dest, src); // Move n-1 disks from auxiliary to destination
}

int main() {
    FAST_IO;
    int n;
    cin >> n;
    cout << (1 << n) - 1 << "\n"; // Minimum number of moves
    solve(n, 1, 3, 2); // Move n disks from 1 to 3 using 2 as auxiliary
    return 0;
}

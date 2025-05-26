#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Speeds up cin/cout by unsyncing with stdio
    cin.tie(nullptr);            // Unties cin from cout for faster I/O

    int n, m, k;
    cin >> n >> m >> k; // Read number of applicants, apartments, and max allowed difference

    vector<int> a(n), b(m);
    for (int &x : a) cin >> x; // Read applicant desired sizes into array a
    for (int &x : b) cin >> x; // Read apartment sizes into array b

    sort(a.begin(), a.end()); // Sort desired sizes (applicants)
    sort(b.begin(), b.end()); // Sort apartment sizes

    int i = 0, j = 0, count = 0; // i → applicant pointer, j → apartment pointer, count → matched applicants

    // Two-pointer traversal
    while (i < n && j < m) {
        if (abs(a[i] - b[j]) <= k) {
            // If apartment size is within acceptable range for applicant
            count++; // Allocate apartment
            i++;     // Move to next applicant
            j++;     // Move to next apartment
        } 
        else if (a[i] < b[j] - k) {
            // Apartment is too big for applicant (even smallest acceptable is less than apartment)
            i++; // Try next applicant
        } 
        else {
            // Apartment is too small for applicant
            j++; // Try next apartment
        }
    }

    cout << count << '\n'; // Output the number of successful allocations
    return 0;
}

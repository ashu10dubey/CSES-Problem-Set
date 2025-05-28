#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast I/O
    cin.tie(nullptr);            // Untie cin and cout for performance

    int n, m;
    cin >> n >> m;               // n = number of tickets, m = number of customers

    multiset<int> tickets;       // Multiset to store tickets (allows duplicates and efficient lookup)
    for (int i = 0; i < n; ++i) {
        int price;
        cin >> price;
        tickets.insert(price);   // O(log n) per insert
    }

    for (int i = 0; i < m; ++i) {
        int max_price;
        cin >> max_price;

        // upper_bound returns first element > max_price
        auto it = tickets.upper_bound(max_price);
        if (it == tickets.begin()) {
            // No ticket found within price range
            cout << -1 << '\n';
        } else {
            --it; // Move to ticket <= max_price
            cout << *it << '\n';
            tickets.erase(it); // Remove ticket from availability (O(log n))
        }
    }

    return 0;
}

/*
-------------------------------------------------------
Time Complexity:
- Insert n tickets into multiset: O(n log n)
- For each of m customers:
    - Lookup + erase: O(log n)
- Total: O((n + m) * log n)

Space Complexity:
- O(n) for storing tickets
-------------------------------------------------------
*/

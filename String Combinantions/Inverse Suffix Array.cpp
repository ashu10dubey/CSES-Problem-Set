#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> sa(n);
    // 1. Read suffix array and convert to 0-based indexing
    for (int i = 0; i < n; ++i) {
        std::cin >> sa[i];
        sa[i]--; // Convert from 1-based to 0-based
    }

    // 2. Compute the rank array (inverse of the suffix array)
    // rank[j] = lexicographical rank of the suffix starting at index j
    std::vector<int> rank(n);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }

    // 3. Assign character classes based on suffix ranks
    std::vector<int> char_class(n);
    // The first suffix in the sorted list gets the smallest character class
    char_class[sa[0]] = 0;

    for (int i = 1; i < n; ++i) {
        int u = sa[i - 1]; // Previous suffix's start index
        int v = sa[i];     // Current suffix's start index

        // Get the ranks of the suffixes starting one position after u and v
        // If u+1 or v+1 is out of bounds, its rank is considered -1 (smallest)
        int rank_u_plus_1 = (u + 1 < n) ? rank[u + 1] : -1;
        int rank_v_plus_1 = (v + 1 < n) ? rank[v + 1] : -1;

        // If the tie is already broken by the next characters, characters can be the same
        if (rank_u_plus_1 < rank_v_plus_1) {
            char_class[v] = char_class[u];
        } else {
            // Otherwise, we must use a strictly larger character to enforce the order
            char_class[v] = char_class[u] + 1;
        }
    }

    // 4. Check if a solution is possible with 26 characters
    if (char_class[sa[n - 1]] >= 26) {
        std::cout << -1 << std::endl;
        return 0;
    }

    // 5. Construct and print the final string
    std::string result(n, ' ');
    for (int i = 0; i < n; ++i) {
        result[i] = 'a' + char_class[i];
    }
    std::cout << result << std::endl;

    return 0;
}
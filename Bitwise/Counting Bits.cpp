#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    cin >> n;
    
    long long total = 0;
    
    // Check each bit position
    for (int k = 0; k < 60; k++) {  // 60 bits is enough for 10^15
        long long cycle_length = 1LL << (k + 1);  // 2^(k+1)
        long long ones_per_cycle = 1LL << k;      // 2^k
        
        // Complete cycles
        long long complete_cycles = n / cycle_length;
        total += complete_cycles * ones_per_cycle;
        
        // Handle remainder
        long long remainder = n % cycle_length;
        long long extra_ones = max(0LL, remainder - ones_per_cycle + 1);
        total += extra_ones;
    }
    
    cout << total << '\n';
    return 0;
}

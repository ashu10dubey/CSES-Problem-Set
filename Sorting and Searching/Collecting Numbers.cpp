#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> pos(n + 1); // pos[x] gives the index of number x in the array
    
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        pos[x] = i;
    }
    
    int rounds = 1;
    for (int i = 2; i <= n; ++i) {
        if (pos[i] < pos[i - 1]) {
            ++rounds;
        }
    }
    
    cout << rounds << endl;
    return 0;
}

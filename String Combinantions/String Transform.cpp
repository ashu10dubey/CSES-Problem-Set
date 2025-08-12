#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string L;
    cin >> L;
    int n = L.size();

    // Step 1: Create sorted first column F
    string F = L;
    sort(F.begin(), F.end());

    // Step 2: Assign occurrence indices
    vector<int> occL(n), occF(n);
    unordered_map<char,int> cntL, cntF;
    for (int i = 0; i < n; i++) {
        occL[i] = cntL[L[i]]++;
    }
    for (int i = 0; i < n; i++) {
        occF[i] = cntF[F[i]]++;
    }

    // Step 3: Build LF mapping
    // char + occurrence uniquely identifies a position
    unordered_map<char, vector<int>> posInF;
    for (int i = 0; i < n; i++) {
        posInF[F[i]].push_back(i);
    }
    vector<int> LF(n);
    for (int i = 0; i < n; i++) {
        LF[i] = posInF[L[i]][occL[i]];
    }

    // Step 4: Reconstruct original
    string res;
    int idx = find(L.begin(), L.end(), '#') - L.begin();
    for (int i = 0; i < n; i++) {
        res.push_back(L[idx]);
        idx = LF[idx];
    }

    // Step 5: Remove '#' and reverse result
    reverse(res.begin(), res.end());
    res.pop_back(); // remove '#'
    cout << res << "\n";

    return 0;
}

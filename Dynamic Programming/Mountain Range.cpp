#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n);
    for(int i = 0; i < n; i++){
        cin >> h[i];
    }

    // ple[i] = index of previous element to the left with h[...] > h[i], or -1 if none
    // nle[i] = index of next element to the right with h[...] > h[i], or -1 if none
    vector<int> ple(n), nle(n);
    {
        vector<int> st;
        st.reserve(n);
        for(int i = 0; i < n; i++){
            while(!st.empty() && h[st.back()] <= h[i])
                st.pop_back();
            ple[i] = st.empty() ? -1 : st.back();
            st.push_back(i);
        }
    }
    {
        vector<int> st;
        st.reserve(n);
        for(int i = n-1; i >= 0; i--){
            while(!st.empty() && h[st.back()] <= h[i])
                st.pop_back();
            nle[i] = st.empty() ? -1 : st.back();
            st.push_back(i);
        }
    }

    // We'll do DP in order of decreasing height:
    // dp[i] = max glides you can do ending at mountain i
    vector<pair<int,int>> order;
    order.reserve(n);
    for(int i = 0; i < n; i++){
        order.emplace_back(h[i], i);
    }
    // sort by height descending
    sort(order.begin(), order.end(),
         [&](auto &a, auto &b){
             return a.first > b.first;
         });

    vector<int> dp(n, 1);
    int ans = 1;
    for(auto &pr : order){
        int i = pr.second;
        int best = 1;
        if(ple[i] != -1) best = max(best, dp[ple[i]] + 1);
        if(nle[i] != -1) best = max(best, dp[nle[i]] + 1);
        dp[i] = best;
        ans = max(ans, best);
    }

    cout << ans << "\n";
    return 0;
}

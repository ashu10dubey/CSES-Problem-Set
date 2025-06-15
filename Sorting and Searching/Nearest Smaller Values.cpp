#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    stack<int> st; // stores indices
    vector<int> res(n);

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.top()] >= a[i])
            st.pop();
        res[i] = st.empty() ? 0 : (st.top() + 1);
        st.push(i);
    }

    for (int i = 0; i < n; ++i)
        cout << res[i] << " ";
    cout << endl;

    return 0;
}

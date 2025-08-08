#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string &s) {
	int n = (int)s.size();
	vector<int> pi(n);
	for (int i = 1; i < n; ++i) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) j = pi[j - 1];
		if (s[i] == s[j]) ++j;
		pi[i] = j;
	}
	return pi;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	if (!(cin >> s)) return 0;
	int n = (int)s.size();
	auto pi = prefix_function(s);
	vector<int> periods;
	int b = pi[n - 1];
	while (b > 0) {
		periods.push_back(n - b);
		b = pi[b - 1];
	}
	periods.push_back(n);
	sort(periods.begin(), periods.end());
	for (int i = 0; i < (int)periods.size(); ++i) {
		if (i) cout << ' ';
		cout << periods[i];
	}
	cout << '\n';
	return 0;
}
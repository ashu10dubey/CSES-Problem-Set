#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;

    int max_count = 1, curr_count = 1;
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] == s[i - 1]) {
            curr_count++;
        } else {
            curr_count = 1;
        }
        if (curr_count > max_count)
            max_count = curr_count;
    }

    cout << max_count << endl;
    return 0;
}

#include <iostream>
#include <list>

using namespace std;

int main() {
    int n;
    cin >> n;

    list<int> children;
    for (int i = 1; i <= n; ++i) {
        children.push_back(i);
    }

    auto it = children.begin();
    while (!children.empty()) {
        // Move to the next child (to eliminate every second)
        ++it;
        if (it == children.end()) it = children.begin();

        cout << *it << " ";
        it = children.erase(it); // Remove the child

        if (it == children.end()) it = children.begin(); // Loop back if at end
    }

    cout << endl;
    return 0;
}

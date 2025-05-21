#include <bits/stdc++.h>
using namespace std;

const int N = 7;
string path;
bool visited[N][N];
int ans = 0;

int dx[4] = {1, -1, 0, 0}; // D, U, R, L
int dy[4] = {0, 0, 1, -1};
char dir[4] = {'D', 'U', 'R', 'L'};

bool is_valid(int x, int y) {
    return (x >= 0 && y >= 0 && x < N && y < N && !visited[x][y]);
}

void dfs(int x, int y, int step) {
    // If reached end too early or too late
    if (x == 6 && y == 0) {
        if (step == 48) ans++;
        return;
    }

    // Early pruning: if we are stuck (U/D blocked and L/R free or vice versa), no use going further
    if ((x == 0 || visited[x - 1][y]) && (x == N - 1 || visited[x + 1][y]) &&
        (y > 0 && !visited[x][y - 1]) && (y < N - 1 && !visited[x][y + 1]))
        return;

    if ((y == 0 || visited[x][y - 1]) && (y == N - 1 || visited[x][y + 1]) &&
        (x > 0 && !visited[x - 1][y]) && (x < N - 1 && !visited[x + 1][y]))
        return;

    visited[x][y] = true;

    char move = path[step];
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if ((move == '?' || move == dir[d]) && is_valid(nx, ny)) {
            dfs(nx, ny, step + 1);
        }
    }

    visited[x][y] = false;
}

int main() {
    cin >> path;
    memset(visited, false, sizeof(visited));
    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}

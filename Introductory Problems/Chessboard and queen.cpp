#include <bits/stdc++.h>
using namespace std;

int board[8][8];
bool col[8], diag1[15], diag2[15];
int countWays = 0;

void solve(int row) {
    if (row == 8) {
        countWays++;
        return;
    }

    for (int c = 0; c < 8; c++) {
        if (board[row][c] == 0 && !col[c] && !diag1[row - c + 7] && !diag2[row + c]) {
            col[c] = diag1[row - c + 7] = diag2[row + c] = true;
            solve(row + 1);
            col[c] = diag1[row - c + 7] = diag2[row + c] = false;
        }
    }
}

int main() {
    for (int i = 0; i < 8; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < 8; j++) {
            board[i][j] = (line[j] == '*') ? 1 : 0;
        }
    }

    solve(0);
    cout << countWays << "\n";
    return 0;
}

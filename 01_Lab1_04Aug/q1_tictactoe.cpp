#include <bits/stdc++.h>
using namespace std;

const int N = 3;
char board[N][N];

bool isWinner(char p) {
    for (int i = 0; i < N; i++) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < N; j++) {
            if (board[i][j] != p) rowWin = false;
            if (board[j][i] != p) colWin = false;
        }
        if (rowWin || colWin) return true;
    }
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < N; i++) {
        if (board[i][i] != p) diag1 = false;
        if (board[i][N - 1 - i] != p) diag2 = false;
    }
    return diag1 || diag2;
}

int main() {
    int x = 0, o = 0, empty = 0;
    cout << "Enter board row by row (X, O, - for empty):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'X') x++;
            else if (board[i][j] == 'O') o++;
            else empty++;
        }
    }

    bool xWin = isWinner('X');
    bool oWin = isWinner('O');

    if (!(x == o || x == o + 1) || (xWin && oWin) ||
        (xWin && x != o + 1) || (oWin && x != o)) {
        cout << "Invalid board\n";
        return 0;
    }

    if (xWin) cout << "X wins\n";
    else if (oWin) cout << "O wins\n";
    else if (empty == 0) cout << "Draw\n";
    else {
        cout << "Game not finished. Next turn: ";
        if (x == o) cout << "X\n";
        else cout << "O\n";
    }
    return 0;
}

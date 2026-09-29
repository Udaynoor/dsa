#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const int MAX_ACTIONS = 2000;

char start[N][N + 1] = {
    "SCDCCXCDCC",
    "CXCCDCCXCC",
    "CCCXCCDCCD",
    "DCCCCXCCCC",
    "CXCDCCCXCC",
    "CCCCXCCDCC",
    "CDXCCCDCCX",
    "CCCCDXCCCC",
    "XCCDCCCCDC",
    "CCCCCCXCCD"
};

char g[N][N + 1];
int visits[N][N];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void run(int type) {
    for (int i = 0; i < N; i++) strcpy(g[i], start[i]);
    memset(visits, 0, sizeof(visits));

    int r = 0, c = 0, totalDirty = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (g[i][j] == 'S') { r = i; c = j; }
            if (g[i][j] == 'D') totalDirty++;
        }

    int cleaned = 0, moves = 0, repeats = 0, actions = 0;
    visits[r][c] = 1;
    srand(1);

    while (actions < MAX_ACTIONS && cleaned < totalDirty) {
        if (g[r][c] == 'D') {
            g[r][c] = 'C';
            cleaned++;
            actions++;
            continue;
        }

        int nr[4], nc[4], cnt = 0;
        for (int d = 0; d < 4; d++) {
            int a = r + dr[d];
            int b = c + dc[d];
            if (a < 0 || a >= N || b < 0 || b >= N) continue;
            if (g[a][b] == 'X') continue;
            nr[cnt] = a;
            nc[cnt] = b;
            cnt++;
        }
        if (cnt == 0) break;

        int pick = rand() % cnt;
        if (type == 2) {
            pick = 0;
            for (int k = 1; k < cnt; k++)
                if (visits[nr[k]][nc[k]] < visits[nr[pick]][nc[pick]]) pick = k;
        }

        r = nr[pick];
        c = nc[pick];
        moves++;
        actions++;
        if (visits[r][c] > 0) repeats++;
        visits[r][c]++;
    }

    if (type == 1) cout << "===== SIMPLE REFLEX AGENT =====\n";
    else cout << "===== MODEL-BASED REFLEX AGENT =====\n";
    cout << "Total dirty cells at start : " << totalDirty << "\n";
    cout << "Dirty cells cleaned        : " << cleaned << "\n";
    cout << "Movements                  : " << moves << "\n";
    cout << "Total actions              : " << actions << "\n";
    cout << "Repeated visits            : " << repeats << "\n";
    cout << "Final grid:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << g[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "Initial grid:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << start[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
    run(1);
    run(2);
    return 0;
}

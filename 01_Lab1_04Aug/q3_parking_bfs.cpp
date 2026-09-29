#include <bits/stdc++.h>
using namespace std;

int R, C;
char grid[20][20];
int dist[20][20], parR[20][20], parC[20][20];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main() {
    cin >> R >> C;
    int er = 0, ec = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
            dist[i][j] = -1;
            if (grid[i][j] == 'E') { er = i; ec = j; }
        }
    }

    queue<pair<int, int>> q;
    q.push({er, ec});
    dist[er][ec] = 0;
    int tr = -1, tc = -1;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (grid[r][c] == 'A') {
            tr = r; tc = c;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (dist[nr][nc] != -1) continue;
            if (grid[nr][nc] == 'X' || grid[nr][nc] == 'O') continue;
            dist[nr][nc] = dist[r][c] + 1;
            parR[nr][nc] = r;
            parC[nr][nc] = c;
            q.push({nr, nc});
        }
    }

    if (tr == -1) {
        cout << "No reachable available slot\n";
        return 0;
    }

    cout << "Nearest A: (" << tr << "," << tc << ")\n";
    cout << "Minimum movements: " << dist[tr][tc] << "\n";

    vector<pair<int, int>> path;
    int r = tr, c = tc;
    while (!(r == er && c == ec)) {
        path.push_back({r, c});
        int pr = parR[r][c];
        int pc = parC[r][c];
        r = pr; c = pc;
    }
    path.push_back({er, ec});
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i + 1 < (int)path.size()) cout << " -> ";
    }
    cout << "\n";

    for (int i = 1; i + 1 < (int)path.size(); i++)
        grid[path[i].first][path[i].second] = '*';

    cout << "Grid with path (*):\n";
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) cout << grid[i][j] << " ";
        cout << "\n";
    }
    return 0;
}

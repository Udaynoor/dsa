#include <bits/stdc++.h>
using namespace std;

const int N = 10;

char grid[N][N + 1] = {
    "SRRRRRRRRG",
    "RRRRRRRRRR",
    "RRRRRXRRRR",
    "RRRRRRRRRR",
    "XRXXXXXXRX",
    "RRRRRRRRRR",
    "RRRRRRRRRR",
    "RRRRXXRRRR",
    "RRRRRRRRRR",
    "RPRRRRRRRR"
};

int energy[N][N], risk[N][N], traffic[N][N];
int parR[N][N], parC[N][N];
int pathR[200], pathC[200], len;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

double stepCost(int r, int c) {
    return 0.4 * 1 + 0.3 * energy[r][c] + 0.2 * risk[r][c] + 0.1 * traffic[r][c];
}

void buildPath(int sr, int sc, int tr, int tc) {
    int tmpR[200], tmpC[200], k = 0;
    int r = tr, c = tc;
    while (!(r == sr && c == sc)) {
        tmpR[k] = r;
        tmpC[k] = c;
        k++;
        int pr = parR[r][c];
        int pc = parC[r][c];
        r = pr;
        c = pc;
    }
    tmpR[k] = sr;
    tmpC[k] = sc;
    k++;
    len = k;
    for (int i = 0; i < k; i++) {
        pathR[i] = tmpR[k - 1 - i];
        pathC[i] = tmpC[k - 1 - i];
    }
}

bool bfs(int sr, int sc, int tr, int tc) {
    int dist[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) dist[i][j] = -1;

    queue<pair<int, int>> q;
    q.push({sr, sc});
    dist[sr][sc] = 0;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        if (r == tr && c == tc) {
            buildPath(sr, sc, tr, tc);
            return true;
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (grid[nr][nc] == 'X' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            parR[nr][nc] = r;
            parC[nr][nc] = c;
            q.push({nr, nc});
        }
    }
    return false;
}

bool dijkstra(int sr, int sc, int tr, int tc) {
    double d[N][N];
    bool done[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            d[i][j] = 1e9;
            done[i][j] = false;
        }
    d[sr][sc] = 0;

    for (int it = 0; it < N * N; it++) {
        int br = -1, bc = -1;
        double best = 1e9;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (!done[i][j] && d[i][j] < best) {
                    best = d[i][j];
                    br = i;
                    bc = j;
                }
        if (br == -1) break;
        done[br][bc] = true;
        for (int k = 0; k < 4; k++) {
            int nr = br + dr[k];
            int nc = bc + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (grid[nr][nc] == 'X') continue;
            double nd = d[br][bc] + stepCost(nr, nc);
            if (nd < d[nr][nc]) {
                d[nr][nc] = nd;
                parR[nr][nc] = br;
                parC[nr][nc] = bc;
            }
        }
    }
    if (d[tr][tc] >= 1e9) return false;
    buildPath(sr, sc, tr, tc);
    return true;
}

double pathCost() {
    double total = 0;
    for (int i = 1; i < len; i++) total += stepCost(pathR[i], pathC[i]);
    return total;
}

void printPath() {
    for (int i = 0; i < len; i++) {
        cout << "(" << pathR[i] << "," << pathC[i] << ")";
        if (i + 1 < len) cout << " ";
    }
    cout << "\n";
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            energy[i][j] = 1;
            risk[i][j] = 1;
            traffic[i][j] = 1;
        }
    for (int i = 2; i <= 6; i++)
        for (int j = 0; j <= 2; j++) {
            energy[i][j] = 10;
            risk[i][j] = 10;
            traffic[i][j] = 10;
        }

    int sr = 0, sc = 0, pr = 0, pc = 0, gr = 0, gc = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'S') { sr = i; sc = j; }
            if (grid[i][j] == 'P') { pr = i; pc = j; }
            if (grid[i][j] == 'G') { gr = i; gc = j; }
        }

    cout << "Grid:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << grid[i][j] << " ";
        cout << "\n";
    }

    cout << "\n===== GOAL-BASED AGENT (BFS) =====\n";
    bfs(sr, sc, pr, pc);
    cout << "Route S->P: ";
    printPath();
    int m1 = len - 1;
    double c1 = pathCost();
    cout << "Movements S->P: " << m1 << "\n";
    bfs(pr, pc, gr, gc);
    cout << "Route P->G: ";
    printPath();
    int m2 = len - 1;
    double c2 = pathCost();
    cout << "Movements P->G: " << m2 << "\n";
    cout << "Total movements: " << m1 + m2 << "\n";
    cout << "Total utility cost of this route: " << c1 + c2 << "\n";

    cout << "\n===== UTILITY-BASED AGENT (Dijkstra) =====\n";
    dijkstra(sr, sc, pr, pc);
    cout << "Route S->P: ";
    printPath();
    int u1 = len - 1;
    double uc1 = pathCost();
    cout << "Movements S->P: " << u1 << "  Cost: " << uc1 << "\n";
    dijkstra(pr, pc, gr, gc);
    cout << "Route P->G: ";
    printPath();
    int u2 = len - 1;
    double uc2 = pathCost();
    cout << "Movements P->G: " << u2 << "  Cost: " << uc2 << "\n";
    cout << "Total movements: " << u1 + u2 << "\n";
    cout << "Total utility cost: " << uc1 + uc2 << "\n";
    return 0;
}

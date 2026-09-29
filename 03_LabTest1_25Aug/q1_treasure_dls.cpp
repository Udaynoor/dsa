#include <bits/stdc++.h>
using namespace std;

const int N = 15;
int grid[N][N];
bool vis[N][N];
int walkCount[N][N];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
string dirName[4] = {"Up", "Down", "Left", "Right"};

int obs[16][2] = {{1,1},{1,2},{1,13},{2,3},{2,12},{3,5},{3,6},{3,11},
                  {4,7},{4,11},{5,11},{10,4},{10,5},{11,8},{11,9},{11,10}};
int tre[5][2] = {{1,3},{2,12},{8,1},{14,2},{14,11}};

int limitD = 60;
int steps = 0, found = 0, totalTreasure = 0, firstSteps = -1;
bool allDone = false;

void dls(int r, int c, int depth) {
    vis[r][c] = true;
    if (depth == limitD) return;

    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (nr < 0 || nr >= N || nc < 0 || nc >= N || grid[nr][nc] == 1) {
            cout << "At (" << r << "," << c << ") look " << dirName[d]
                 << ": obstacle/boundary -> change the path\n";
            continue;
        }
        if (vis[nr][nc]) continue;

        steps++;
        walkCount[nr][nc]++;

        if (grid[nr][nc] == 2) {
            found++;
            grid[nr][nc] = 0;
            cout << "At (" << r << "," << c << ") look " << dirName[d]
                 << ": treasure -> grab the item at (" << nr << "," << nc
                 << ") [step " << steps << ", depth " << depth + 1 << "]\n";
            if (firstSteps == -1) firstSteps = steps;
            if (found == totalTreasure) {
                allDone = true;
                return;
            }
        } else {
            cout << "At (" << r << "," << c << ") look " << dirName[d]
                 << ": empty -> move ahead to (" << nr << "," << nc
                 << ") [step " << steps << ", depth " << depth + 1 << "]\n";
        }

        dls(nr, nc, depth + 1);
        if (allDone) return;

        steps++;
        walkCount[r][c]++;
        cout << "Dead end/finished -> step back to (" << r << "," << c
             << ") [step " << steps << "]\n";
    }
}

int main() {
    for (int i = 0; i < 16; i++) grid[obs[i][0]][obs[i][1]] = 1;

    for (int i = 0; i < 5; i++) {
        int r = tre[i][0], c = tre[i][1];
        if (grid[r][c] == 1) {
            cout << "Conflict: (" << r << "," << c
                 << ") is both obstacle and treasure. Treated as OBSTACLE, treasure ignored.\n";
        } else {
            grid[r][c] = 2;
            totalTreasure++;
        }
    }

    int sr = N / 2, sc = N / 2;
    walkCount[sr][sc] = 1;
    cout << "Start at (" << sr << "," << sc << "), depth limit = " << limitD
         << ", reachable treasures = " << totalTreasure << "\n\n";

    dls(sr, sc, 0);

    cout << "\nTreasures found: " << found << " of " << totalTreasure << "\n";
    cout << "Steps to first treasure: " << firstSteps << "\n";
    if (allDone) cout << "Steps to all treasures: " << steps << "\n";
    else cout << "Not all treasures found within depth limit\n";

    cout << "\nRepeated cells (entered more than once):\n";
    int repeated = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (walkCount[i][j] > 1) {
                cout << "(" << i << "," << j << ") x" << walkCount[i][j] << "  ";
                repeated++;
            }
    cout << "\nTotal repeated cells: " << repeated << "\n";

    cout << "\nMap: # obstacle, S start, digit = times entered, . = never visited\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1) cout << "# ";
            else if (i == sr && j == sc) cout << "S ";
            else if (walkCount[i][j] == 0) cout << ". ";
            else cout << walkCount[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}

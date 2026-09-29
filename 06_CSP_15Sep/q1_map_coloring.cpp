#include <bits/stdc++.h>
using namespace std;

const int n = 5;
int graph[5][5] = {
    {0, 1, 1, 0, 0},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 0}
};
int color[5];
string colorName[4] = {"", "Red", "Green", "Blue"};
string varName = "ABCDE";
int assignments, backtracks, conflictWith;

bool isSafe(int v, int c) {
    for (int i = 0; i < n; i++) {
        if (graph[v][i] && color[i] == c) {
            conflictWith = i;
            return false;
        }
    }
    return true;
}

bool solveBT(int v) {
    if (v == n) return true;
    for (int c = 1; c <= 3; c++) {
        cout << "Variable " << varName[v] << ": try " << colorName[c];
        if (isSafe(v, c)) {
            color[v] = c;
            assignments++;
            cout << " -> OK, assigned\n";
            if (solveBT(v + 1)) return true;
            color[v] = 0;
            backtracks++;
            cout << "Backtrack: remove " << varName[v] << " = " << colorName[c] << "\n";
        } else {
            cout << " -> conflict with " << varName[conflictWith] << " (" << colorName[c] << ")\n";
        }
    }
    return false;
}

int legalCount(int v) {
    int cnt = 0;
    for (int c = 1; c <= 3; c++)
        if (isSafe(v, c)) cnt++;
    return cnt;
}

bool solveMRV(int done) {
    if (done == n) return true;

    int best = -1, bestCnt = 100;
    for (int v = 0; v < n; v++) {
        if (color[v] == 0) {
            int cnt = legalCount(v);
            if (cnt < bestCnt) {
                bestCnt = cnt;
                best = v;
            }
        }
    }

    cout << "Select " << varName[best] << " (legal values: ";
    for (int c = 1; c <= 3; c++)
        if (isSafe(best, c)) cout << colorName[c] << " ";
    cout << ")\n";

    for (int c = 1; c <= 3; c++) {
        if (isSafe(best, c)) {
            color[best] = c;
            assignments++;
            cout << "  Assign " << varName[best] << " = " << colorName[c] << "\n";
            if (solveMRV(done + 1)) return true;
            color[best] = 0;
            backtracks++;
            cout << "  Backtrack: remove " << varName[best] << " = " << colorName[c] << "\n";
        }
    }
    return false;
}

void printResult() {
    for (int i = 0; i < n; i++)
        cout << varName[i] << " = " << colorName[color[i]] << "\n";
}

int main() {
    cout << "===== BACKTRACKING (order A,B,C,D,E) =====\n";
    for (int i = 0; i < n; i++) color[i] = 0;
    assignments = 0;
    backtracks = 0;
    solveBT(0);
    cout << "Final assignment:\n";
    printResult();
    cout << "Assignments: " << assignments << "  Backtracks: " << backtracks << "\n\n";

    cout << "===== MRV =====\n";
    for (int i = 0; i < n; i++) color[i] = 0;
    assignments = 0;
    backtracks = 0;
    solveMRV(0);
    cout << "Final assignment:\n";
    printResult();
    cout << "Assignments: " << assignments << "  Backtracks: " << backtracks << "\n";
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int n = 4;
string name[4] = {"AI", "DBMS", "OS", "CN"};
int startDom[4][5] = {
    {0, 1, 1, 1, 0},
    {0, 1, 1, 0, 1},
    {0, 0, 1, 1, 1},
    {0, 1, 0, 1, 1}
};
int con[4][4] = {
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0}
};
int slot[4];
int dom[4][5];
int assignments, backtracks, conflictWith;

bool isSafe(int v, int s) {
    for (int i = 0; i < n; i++) {
        if (con[v][i] && slot[i] == s) {
            conflictWith = i;
            return false;
        }
    }
    return true;
}

void reset() {
    for (int i = 0; i < n; i++) {
        slot[i] = 0;
        for (int s = 0; s < 5; s++) dom[i][s] = startDom[i][s];
    }
    assignments = 0;
    backtracks = 0;
}

void printDomains() {
    for (int i = 0; i < n; i++) {
        cout << "    " << name[i] << " = {";
        bool first = true;
        for (int s = 1; s <= 4; s++)
            if (dom[i][s]) {
                if (!first) cout << ",";
                cout << s;
                first = false;
            }
        cout << "}\n";
    }
}

void printTimetable() {
    for (int i = 0; i < n; i++)
        cout << name[i] << " -> slot " << slot[i] << "\n";
    cout << "Assignments: " << assignments << "  Backtracks: " << backtracks << "\n";
}

bool solveBT(int v) {
    if (v == n) return true;
    for (int s = 1; s <= 4; s++) {
        if (!startDom[v][s]) continue;
        cout << "Variable " << name[v] << ": try slot " << s;
        if (isSafe(v, s)) {
            slot[v] = s;
            assignments++;
            cout << " -> OK, assigned\n";
            if (solveBT(v + 1)) return true;
            slot[v] = 0;
            backtracks++;
            cout << "Backtrack: remove " << name[v] << " = " << s << "\n";
        } else {
            cout << " -> conflict with " << name[conflictWith] << " (slot " << s << ")\n";
        }
    }
    return false;
}

int legalCount(int v) {
    int cnt = 0;
    for (int s = 1; s <= 4; s++)
        if (startDom[v][s] && isSafe(v, s)) cnt++;
    return cnt;
}

bool solveMRV(int done) {
    if (done == n) return true;
    int best = -1, bestCnt = 100;
    for (int v = 0; v < n; v++) {
        if (slot[v] == 0) {
            int cnt = legalCount(v);
            if (cnt < bestCnt) {
                bestCnt = cnt;
                best = v;
            }
        }
    }
    cout << "Select " << name[best] << " (legal slots: ";
    for (int s = 1; s <= 4; s++)
        if (startDom[best][s] && isSafe(best, s)) cout << s << " ";
    cout << ")\n";

    for (int s = 1; s <= 4; s++) {
        if (startDom[best][s] && isSafe(best, s)) {
            slot[best] = s;
            assignments++;
            cout << "  Assign " << name[best] << " = " << s << "\n";
            if (solveMRV(done + 1)) return true;
            slot[best] = 0;
            backtracks++;
            cout << "  Backtrack: remove " << name[best] << " = " << s << "\n";
        }
    }
    return false;
}

int domSize(int v) {
    int cnt = 0;
    for (int s = 1; s <= 4; s++) cnt += dom[v][s];
    return cnt;
}

bool solveFC(int done) {
    if (done == n) return true;

    int best = -1;
    for (int v = 0; v < n; v++)
        if (slot[v] == 0 && (best == -1 || domSize(v) < domSize(best))) best = v;

    cout << "Select " << name[best] << " (domain size " << domSize(best) << ")\n";

    for (int s = 1; s <= 4; s++) {
        if (!dom[best][s]) continue;

        int saved[4][5];
        memcpy(saved, dom, sizeof(dom));

        slot[best] = s;
        assignments++;
        cout << "  Assign " << name[best] << " = " << s << "\n";

        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (slot[i] == 0 && con[best][i] && dom[i][s]) {
                dom[i][s] = 0;
                cout << "  Forward check: remove " << s << " from " << name[i] << "\n";
                if (domSize(i) == 0) {
                    cout << "  Domain of " << name[i] << " is empty!\n";
                    ok = false;
                }
            }
        }
        cout << "  Updated domains:\n";
        printDomains();

        if (ok && solveFC(done + 1)) return true;

        memcpy(dom, saved, sizeof(dom));
        slot[best] = 0;
        backtracks++;
        cout << "  Backtrack: remove " << name[best] << " = " << s << " and restore domains\n";
    }
    return false;
}

int main() {
    cout << "===== BACKTRACKING (order AI, DBMS, OS, CN) =====\n";
    reset();
    solveBT(0);
    printTimetable();

    cout << "\n===== MRV =====\n";
    reset();
    solveMRV(0);
    printTimetable();

    cout << "\n===== FORWARD CHECKING (with MRV choice) =====\n";
    reset();
    cout << "Initial domains:\n";
    printDomains();
    solveFC(0);
    printTimetable();
    return 0;
}

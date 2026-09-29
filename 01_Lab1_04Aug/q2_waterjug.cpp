#include <bits/stdc++.h>
using namespace std;

int capA = 4, capB = 3, goal = 2;
bool vis[10][10];
int parA[10][10], parB[10][10], op[10][10];
string opName[7] = {"Start", "Fill 4L jug", "Fill 3L jug", "Empty 4L jug",
                    "Empty 3L jug", "Pour 4L into 3L", "Pour 3L into 4L"};

void nextStates(int a, int b, int na[], int nb[]) {
    na[1] = capA; nb[1] = b;
    na[2] = a;    nb[2] = capB;
    na[3] = 0;    nb[3] = b;
    na[4] = a;    nb[4] = 0;
    int t = min(a, capB - b);
    na[5] = a - t; nb[5] = b + t;
    t = min(b, capA - a);
    na[6] = a + t; nb[6] = b - t;
}

void printPath(int a, int b) {
    if (op[a][b] == 0) {
        cout << "Start            -> (" << a << "," << b << ")\n";
        return;
    }
    printPath(parA[a][b], parB[a][b]);
    cout << opName[op[a][b]];
    for (int k = opName[op[a][b]].size(); k < 16; k++) cout << " ";
    cout << " -> (" << a << "," << b << ")\n";
}

int main() {
    queue<pair<int, int>> q;
    q.push({0, 0});
    vis[0][0] = true;
    op[0][0] = 0;

    while (!q.empty()) {
        int a = q.front().first;
        int b = q.front().second;
        q.pop();

        if (a == goal) {
            cout << "State = (4L jug, 3L jug)\n";
            printPath(a, b);
            return 0;
        }

        int na[7], nb[7];
        nextStates(a, b, na, nb);
        for (int k = 1; k <= 6; k++) {
            if (!vis[na[k]][nb[k]]) {
                vis[na[k]][nb[k]] = true;
                parA[na[k]][nb[k]] = a;
                parB[na[k]][nb[k]] = b;
                op[na[k]][nb[k]] = k;
                q.push({na[k], nb[k]});
            }
        }
    }
    cout << "No solution\n";
    return 0;
}

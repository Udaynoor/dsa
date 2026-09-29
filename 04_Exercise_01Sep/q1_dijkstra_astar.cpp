#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int INF = 1000000;
int w[N][N];
int h[N] = {6, 2, 5, 6, 4, 0};

void printPath(int par[], int goal) {
    vector<int> path;
    for (int v = goal; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        cout << (char)('a' + path[i]);
        if (i + 1 < (int)path.size()) cout << " -> ";
    }
    cout << "\n";
}

void dijkstra(int src, int goal) {
    int dist[N], par[N];
    bool done[N];
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        par[i] = -1;
        done[i] = false;
    }
    dist[src] = 0;

    cout << "===== DIJKSTRA =====\n";
    int expanded = 0;
    for (int it = 0; it < N; it++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!done[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INF) break;

        done[u] = true;
        expanded++;
        cout << "Pick " << (char)('a' + u) << " with dist = " << dist[u] << "\n";
        if (u == goal) break;

        for (int v = 0; v < N; v++) {
            if (w[u][v] > 0 && dist[u] + w[u][v] < dist[v]) {
                dist[v] = dist[u] + w[u][v];
                par[v] = u;
            }
        }
    }
    if (dist[goal] == INF) {
        cout << "No path\n";
        return;
    }
    cout << "Shortest cost: " << dist[goal] << "\n";
    cout << "Path: ";
    printPath(par, goal);
    cout << "Nodes expanded: " << expanded << "\n\n";
}

void astar(int src, int goal) {
    int g[N], par[N];
    bool inOpen[N];
    for (int i = 0; i < N; i++) {
        g[i] = INF;
        par[i] = -1;
        inOpen[i] = false;
    }
    g[src] = 0;
    inOpen[src] = true;

    cout << "===== A* =====\n";
    int expanded = 0;
    while (true) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (inOpen[i] && (u == -1 || g[i] + h[i] < g[u] + h[u])) u = i;
        if (u == -1) break;

        inOpen[u] = false;
        expanded++;
        cout << "Pick " << (char)('a' + u) << ": g = " << g[u] << ", h = " << h[u]
             << ", f = " << g[u] + h[u] << "\n";
        if (u == goal) break;

        for (int v = 0; v < N; v++) {
            if (w[u][v] > 0 && g[u] + w[u][v] < g[v]) {
                g[v] = g[u] + w[u][v];
                par[v] = u;
                inOpen[v] = true;
            }
        }
    }
    if (g[goal] == INF) {
        cout << "No path\n";
        return;
    }
    cout << "Shortest cost: " << g[goal] << "\n";
    cout << "Path: ";
    printPath(par, goal);
    cout << "Nodes expanded: " << expanded << "\n";
}

int main() {
    int m;
    cout << "Enter number of edges, then each edge as: u v weight (letters a-f)\n";
    cin >> m;
    for (int i = 0; i < m; i++) {
        char u, v;
        int cost;
        cin >> u >> v >> cost;
        w[u - 'a'][v - 'a'] = cost;
        w[v - 'a'][u - 'a'] = cost;
    }
    dijkstra(0, 5);
    astar(0, 5);
    return 0;
}

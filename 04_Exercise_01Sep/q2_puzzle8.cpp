#include <bits/stdc++.h>
using namespace std;

string startState = "123046758";
string goalState = "123456780";
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<string> nextStates(string s) {
    vector<string> res;
    int p = s.find('0');
    int r = p / 3, c = p % 3;
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
        string t = s;
        swap(t[p], t[nr * 3 + nc]);
        res.push_back(t);
    }
    return res;
}

void printBoard(string s) {
    for (int i = 0; i < 9; i++) {
        if (s[i] == '0') cout << "# ";
        else cout << s[i] << " ";
        if (i % 3 == 2) cout << "\n";
    }
}

void printPathList(vector<string> path) {
    for (int i = 0; i < (int)path.size(); i++) {
        cout << "Step " << i << ":\n";
        printBoard(path[i]);
        cout << "\n";
    }
    cout << "Moves: " << path.size() - 1 << "\n";
}

vector<string> buildPath(map<string, string>& par, string s) {
    vector<string> path;
    while (s != "") {
        path.push_back(s);
        s = par[s];
    }
    reverse(path.begin(), path.end());
    return path;
}

void bfs() {
    cout << "===== BFS =====\n";
    map<string, string> par;
    queue<string> q;
    q.push(startState);
    par[startState] = "";
    int expanded = 0;

    while (!q.empty()) {
        string s = q.front();
        q.pop();
        expanded++;
        if (s == goalState) {
            printPathList(buildPath(par, s));
            cout << "States expanded: " << expanded << "\n\n";
            return;
        }
        vector<string> nx = nextStates(s);
        for (int i = 0; i < (int)nx.size(); i++) {
            if (par.count(nx[i]) == 0) {
                par[nx[i]] = s;
                q.push(nx[i]);
            }
        }
    }
}

map<string, int> bestDepth;
vector<string> curPath;
vector<string> answer;
int dfsLimit = 12;
int dfsExpanded = 0;

bool dfs(string s, int depth) {
    curPath.push_back(s);
    if (s == goalState) {
        answer = curPath;
        return true;
    }
    if (depth < dfsLimit) {
        dfsExpanded++;
        vector<string> nx = nextStates(s);
        for (int i = 0; i < (int)nx.size(); i++) {
            if (bestDepth.count(nx[i]) && bestDepth[nx[i]] <= depth + 1) continue;
            bestDepth[nx[i]] = depth + 1;
            if (dfs(nx[i], depth + 1)) return true;
        }
    }
    curPath.pop_back();
    return false;
}

void runDfs() {
    cout << "===== DFS (depth limit " << dfsLimit << ") =====\n";
    bestDepth[startState] = 0;
    if (dfs(startState, 0)) {
        printPathList(answer);
        cout << "States expanded: " << dfsExpanded << "\n\n";
    } else {
        cout << "No solution within depth limit\n\n";
    }
}

int heuristic(string s) {
    int cnt = 0;
    for (int i = 0; i < 9; i++)
        if (s[i] != '0' && s[i] != goalState[i]) cnt++;
    return cnt;
}

void astar() {
    cout << "===== A* (f = g + h, h = mismatched tiles) =====\n";
    map<string, int> g;
    map<string, string> par;
    priority_queue<pair<int, string>, vector<pair<int, string>>,
                   greater<pair<int, string>>> pq;
    g[startState] = 0;
    par[startState] = "";
    pq.push({heuristic(startState), startState});
    int expanded = 0;

    while (!pq.empty()) {
        string s = pq.top().second;
        int f = pq.top().first;
        pq.pop();
        if (f > g[s] + heuristic(s)) continue;
        expanded++;
        cout << "Expand state " << s << ": g = " << g[s] << ", h = " << heuristic(s)
             << ", f = " << f << "\n";
        if (s == goalState) {
            cout << "\n";
            printPathList(buildPath(par, s));
            cout << "States expanded: " << expanded << "\n";
            return;
        }
        vector<string> nx = nextStates(s);
        for (int i = 0; i < (int)nx.size(); i++) {
            int ng = g[s] + 1;
            if (g.count(nx[i]) == 0 || ng < g[nx[i]]) {
                g[nx[i]] = ng;
                par[nx[i]] = s;
                pq.push({ng + heuristic(nx[i]), nx[i]});
            }
        }
    }
}

int main() {
    bfs();
    runDfs();
    astar();
    return 0;
}

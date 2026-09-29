#include <bits/stdc++.h>
using namespace std;

const int K = 7;
double px[8] = {0, 2, 5, 6, 8, 1, 7, 3};
double py[8] = {0, 6, 2, 7, 3, 4, 6, 1};

double dist(int a, int b) {
    return sqrt((px[a] - px[b]) * (px[a] - px[b]) + (py[a] - py[b]) * (py[a] - py[b]));
}

double cost(int route[]) {
    double total = dist(0, route[0]);
    for (int i = 0; i + 1 < K; i++) total += dist(route[i], route[i + 1]);
    total += dist(route[K - 1], 0);
    return total;
}

void randomRoute(int route[]) {
    for (int i = 0; i < K; i++) route[i] = i + 1;
    for (int i = K - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(route[i], route[j]);
    }
}

void printRoute(int route[]) {
    cout << "W ";
    for (int i = 0; i < K; i++) cout << (char)('A' + route[i] - 1) << " ";
    cout << "W";
}

int main() {
    srand(7);
    int route[K];
    randomRoute(route);

    double cur = cost(route);
    cout << "Initial route: ";
    printRoute(route);
    cout << "\nInitial cost: " << cur << "\n\n";

    int iterations = 0;
    while (true) {
        iterations++;
        double bestCost = 1e9;
        int bi = -1, bj = -1;

        for (int i = 0; i < K; i++) {
            for (int j = i + 1; j < K; j++) {
                swap(route[i], route[j]);
                double c = cost(route);
                swap(route[i], route[j]);
                if (c < bestCost) {
                    bestCost = c;
                    bi = i;
                    bj = j;
                }
            }
        }

        cout << "Iteration " << iterations << ": best neighbour (swap "
             << (char)('A' + route[bi] - 1) << "," << (char)('A' + route[bj] - 1)
             << ") cost = " << bestCost;

        if (bestCost < cur) {
            swap(route[bi], route[bj]);
            cur = bestCost;
            cout << "  -> moved\n  route: ";
            printRoute(route);
            cout << "\n";
        } else {
            cout << "  -> no improvement, stop\n";
            break;
        }
    }

    cout << "\nFinal route: ";
    printRoute(route);
    cout << "\nFinal cost: " << cur << "\n";
    cout << "Number of iterations: " << iterations << "\n";
    return 0;
}

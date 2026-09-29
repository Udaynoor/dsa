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
    int route[K], bestRoute[K];
    randomRoute(route);

    double curCost = cost(route);
    double bestCost = curCost;
    for (int i = 0; i < K; i++) bestRoute[i] = route[i];

    cout << "Initial route: ";
    printRoute(route);
    cout << "\nInitial cost: " << curCost << "\n\n";

    double T = 100, alpha = 0.95, Tmin = 0.1;
    int iterations = 0;

    while (T > Tmin) {
        iterations++;
        int i = rand() % K;
        int j = rand() % K;
        while (j == i) j = rand() % K;

        swap(route[i], route[j]);
        double newCost = cost(route);
        double dE = newCost - curCost;

        bool accept = false;
        if (dE < 0) accept = true;
        else {
            double r = (double)rand() / RAND_MAX;
            double P = exp(-dE / T);
            if (r < P) accept = true;
        }

        if (accept) {
            curCost = newCost;
            if (curCost < bestCost) {
                bestCost = curCost;
                for (int k = 0; k < K; k++) bestRoute[k] = route[k];
            }
        } else {
            swap(route[i], route[j]);
        }

        cout << "Iter " << iterations << "  T = " << T << "  dE = " << dE
             << "  " << (accept ? "ACCEPTED" : "REJECTED")
             << "  current cost = " << curCost << "  route: ";
        printRoute(route);
        cout << "\n";

        T = alpha * T;
    }

    cout << "\nBest route: ";
    printRoute(bestRoute);
    cout << "\nBest cost: " << bestCost << "\n";
    cout << "Number of iterations: " << iterations << "\n";
    return 0;
}

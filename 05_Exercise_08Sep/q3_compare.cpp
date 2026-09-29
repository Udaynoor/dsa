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

int iterations;

double hillClimb(int route[]) {
    double cur = cost(route);
    iterations = 0;
    while (true) {
        iterations++;
        double bestCost = 1e9;
        int bi = -1, bj = -1;
        for (int i = 0; i < K; i++)
            for (int j = i + 1; j < K; j++) {
                swap(route[i], route[j]);
                double c = cost(route);
                swap(route[i], route[j]);
                if (c < bestCost) { bestCost = c; bi = i; bj = j; }
            }
        if (bestCost < cur) {
            swap(route[bi], route[bj]);
            cur = bestCost;
        } else break;
    }
    return cur;
}

double annealing(int route[]) {
    double curCost = cost(route), bestCost = curCost;
    double T = 100, alpha = 0.95, Tmin = 0.1;
    iterations = 0;
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
        else if ((double)rand() / RAND_MAX < exp(-dE / T)) accept = true;
        if (accept) {
            curCost = newCost;
            if (curCost < bestCost) bestCost = curCost;
        } else swap(route[i], route[j]);
        T = alpha * T;
    }
    return bestCost;
}

double bruteForce() {
    int route[K];
    for (int i = 0; i < K; i++) route[i] = i + 1;
    double best = 1e9;
    do {
        best = min(best, cost(route));
    } while (next_permutation(route, route + K));
    return best;
}

int main() {
    srand(7);
    int runs = 5;
    double hcBest = 1e9, hcWorst = 0, hcSum = 0, hcIter = 0;
    double saBest = 1e9, saWorst = 0, saSum = 0, saIter = 0;

    cout << "Run   HC cost   HC iter   SA cost   SA iter\n";
    for (int t = 1; t <= runs; t++) {
        int start[K], r1[K], r2[K];
        randomRoute(start);
        for (int i = 0; i < K; i++) { r1[i] = start[i]; r2[i] = start[i]; }

        double hc = hillClimb(r1);
        int hcIt = iterations;
        double sa = annealing(r2);
        int saIt = iterations;

        cout << t << "     " << hc << "    " << hcIt << "         " << sa << "    " << saIt << "\n";

        hcBest = min(hcBest, hc);
        hcWorst = max(hcWorst, hc);
        hcSum += hc;
        hcIter += hcIt;
        saBest = min(saBest, sa);
        saWorst = max(saWorst, sa);
        saSum += sa;
        saIter += saIt;
    }

    cout << "\nHill Climbing:       best " << hcBest << "  worst " << hcWorst
         << "  average " << hcSum / runs << "  avg iterations " << hcIter / runs << "\n";
    cout << "Simulated Annealing: best " << saBest << "  worst " << saWorst
         << "  average " << saSum / runs << "  avg iterations " << saIter / runs << "\n";
    cout << "True optimum (brute force over 5040 routes): " << bruteForce() << "\n";
    return 0;
}

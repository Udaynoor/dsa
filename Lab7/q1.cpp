#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int fitness(string s) {
    int x = 0;

    for(char c : s)
        x = x * 2 + (c - '0');

    return 15 * x - x * x;
}

string randomGene() {
    string s = "";

    for(int i = 0; i < 4; i++)
        s += char('0' + rand() % 2);

    return s;
}

string selectParent(vector<string> pop) {

    int total = 0;

    for(string s : pop)
        total += fitness(s);

    int r = rand() % total;

    for(string s : pop) {
        r -= fitness(s);

        if(r < 0)
            return s;
    }

    return pop[0];
}

void crossover(string &a, string &b) {

    int point = 1 + rand() % 3;

    for(int i = point; i < 4; i++)
        swap(a[i], b[i]);
}

void mutation(string &s) {

    int pos = rand() % 4;

    if(rand() % 100 < 5)
        s[pos] = (s[pos] == '0' ? '1' : '0');
}

int main() {

    srand(time(0));

    int populationSize = 6;
    int generations = 10;

    vector<string> pop;

    for(int i = 0; i < populationSize; i++)
        pop.push_back(randomGene());

    string best = pop[0];

    for(int gen = 0; gen < generations; gen++) {

        cout << "\nGeneration " << gen + 1 << "\n";

        for(string s : pop) {

            cout << s
                 << " x=";

            int x = stoi(s, nullptr, 2);

            cout << x
                 << " fitness="
                 << fitness(s) << "\n";

            if(fitness(s) > fitness(best))
                best = s;
        }

        vector<string> next;

        while(next.size() < populationSize) {

            string p1 = selectParent(pop);
            string p2 = selectParent(pop);

            crossover(p1, p2);

            mutation(p1);
            mutation(p2);

            next.push_back(p1);

            if(next.size() < populationSize)
                next.push_back(p2);
        }

        pop = next;
    }

    int x = stoi(best, nullptr, 2);

    cout << "\nBest chromosome: " << best << "\n";
    cout << "Best x: " << x << "\n";
    cout << "Maximum fitness: " << fitness(best) << "\n";

    return 0;
}
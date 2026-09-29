#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int weight[] = {7, 2, 1, 9};
int value[] = {500, 400, 700, 200};

int getWeight(string s) {

    int w = 0;

    for(int i = 0; i < 4; i++)
        if(s[i] == '1')
            w += weight[i];

    return w;
}

int fitness(string s) {

    int w = getWeight(s);

    if(w > 15)
        return 0;

    int val = 0;

    for(int i = 0; i < 4; i++)
        if(s[i] == '1')
            val += value[i];

    return val;
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

    if(total == 0)
        return pop[rand() % pop.size()];

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

        cout << "\nGeneration "
             << gen + 1 << "\n";

        for(string s : pop) {

            cout << s
                 << " Weight = "
                 << getWeight(s)
                 << " Value = "
                 << fitness(s)
                 << "\n";

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

    cout << "\nBest chromosome: "
         << best << "\n";

    cout << "Weight: "
         << getWeight(best) << " kg\n";

    cout << "Value: Rs. "
         << fitness(best) << "\n";

    return 0;
}
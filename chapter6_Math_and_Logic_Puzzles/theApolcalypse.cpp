#include <time.h>

#include <chrono>
#include <iostream>
#include <random>

using namespace std;

void apocalypse_simulation(const int& nFamily, const int& nExp) {
    srand((int)chrono::high_resolution_clock::now().time_since_epoch().count());

    long long boys = 0;

    for (int i = 0; i < nExp; ++i) {
        long long temp_boys = 0;
        for (int j = 0; j < nFamily; ++j) {
            while (rand() % 2 != 0) {
                temp_boys++;
            }
        }
        cout << "Experiment #" << i << "  b: " << temp_boys
             << "  g: " << nFamily << endl;
        boys += temp_boys;
    }

    cout << nExp << " simulations completed." << endl;
    cout << "Average result:\nb: " << (double)boys / nExp << "  g: " << nFamily
         << endl;
}

void natrual_simulation(const int& nFamily, const int& nExp) {
    srand((int)chrono::high_resolution_clock::now().time_since_epoch().count());

    long long boys = 0;
    long long girls = 0;

    for (int i = 0; i < nExp; ++i) {
        long long temp_boys = 0;
        long long temp_girls = 0;
        for (int j = 0; j < nFamily; ++j) {
            if (rand() % 2 == 0) {
                temp_girls++;
            } else {
                temp_boys++;
            }
        }
        cout << "Experiment #" << i << "  b: " << temp_boys
             << "  g: " << temp_girls << endl;
        boys += temp_boys;
        girls += temp_girls;
    }

    cout << nExp << " simulations completed." << endl;
    cout << "Average result:\nb: " << (double)boys / nExp
         << "  g: " << (double)girls / nExp << endl;
}

int main() {
    const int nFamily = 5000;
    const int nExperiment = 100;

    cout << "apocalypse simulation" << endl;

    apocalypse_simulation(nFamily, nExperiment);

    cout << "natrual simulation" << endl;

    natrual_simulation(nFamily, nExperiment);

    return 0;
}
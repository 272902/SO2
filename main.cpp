#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <semaphore>
#include <cstdlib>

using namespace std;

void philosopher(int id, int numIterations) {
}

void eat() {
}

void think() {
}

int main() {
    int numPhilosophers = 5;
    if (numPhilosophers < 2) {
        cerr << "There has to be at least 2 philosophers." << endl;
        return 1;
    }

    const int numIterations = 5; // iteration number (1 iteration - thinking, eating)

    // Semaphore with plihosophers number
    counting_semaphore<> table(numPhilosophers - 1);

    return 0;
}
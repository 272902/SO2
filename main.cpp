#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
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

    // Mutex forks
    vector<mutex> forks(numPhilosophers);

    const int numIterations = 5; // iteration number (1 iteration - thinking, eating)

    // Semaphore with plihosophers number
    counting_semaphore<> table(numPhilosophers - 1);

    // Threads for philosophers
    vector<thread> philosophers;

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.emplace_back(philosopher, i, numIterations,
                                  ref(forks[i]),
                                  ref(forks[(i + 1) % numPhilosophers]),
                                  ref(table));
    }

    return 0;
}
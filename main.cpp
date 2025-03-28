#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <semaphore>
#include <cstdlib>

using namespace std;

void philosopher(int id, mutex& leftFork, mutex& rightFork, counting_semaphore<>& table) {
    while(true) {
        think(id);
        eat(id);
    }
}

void eat(int id) {
    cout << "Philosopher " << id << " is eating." << endl;
    //Eating for a duration of random time (between 100 and 300 ms)
    this_thread::sleep_for(chrono::milliseconds(100 + rand() % 200));
}

void think(int id) {
    cout << "Philosopher " << id << " is thinking." << endl;
    //Thinking for a duration of random time (between 100 and 300 ms)
    this_thread::sleep_for(chrono::milliseconds(100 + rand() % 200));
}

int main(int argc, char* argv[]) {

    int numPhilosophers = 5; // default philosophers number

    if(argc >= 2) {
        numPhilosophers = atoi(argv[1]);
        if(numPhilosophers < 2) {
            cerr << "There has to be at least 2 philosophers." << endl;
            return 1;
        }
    }

    // Mutex forks
    vector<mutex> forks(numPhilosophers);

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

    for (auto &t : philosophers) {
        t.join();
    }

    return 0;
}

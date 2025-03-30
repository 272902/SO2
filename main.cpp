#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <semaphore>
#include <cstdlib>

using namespace std;

mutex printMutex;

void eat(int id, mutex& mo) {
    {
        lock_guard<mutex> lock(mo);
        cout << "\t\t\t\t\t\t\t\tPhilosopher " << id << " is eating." << endl;
    }
    //Eating for a duration of random time (between 1000 and 2000 ms)
    this_thread::sleep_for(chrono::milliseconds(1000 + rand() % 2000));
}

void think(int id, mutex& mo) {
    {
        lock_guard<mutex> lock(mo);
        cout << "Philosopher " << id << " is thinking." << endl;
    }
    //Thinking for a duration of random time (between 1000 and 2000 ms)
    this_thread::sleep_for(chrono::milliseconds(1000 + rand() % 2000));
}

void is_hungry(int id, mutex& mo) {
    {
        lock_guard<mutex> lock(mo);
        cout << "\t\t\tPhilosopher " << id << " is hungry." << endl;
    }
    //Thinking for a duration of random time (between 1000 and 2000 ms)
    this_thread::sleep_for(chrono::milliseconds(1000 + rand() % 2000));
}

void philosopher(int id, mutex& leftFork, mutex& rightFork, counting_semaphore<>& table, mutex& mo) {
    while(true) {
        while (true) {
            think(id, mo);
            is_hungry(id, mo);
            table.acquire();
    
            if (id % 2 == 0) {
                lock_guard<mutex> rightLock(rightFork);
                lock_guard<mutex> leftLock(leftFork);
                eat(id, mo);
            } else {
                lock_guard<mutex> leftLock(leftFork);
                lock_guard<mutex> rightLock(rightFork);
                eat(id, mo);
            }
            
            table.release();
        }

        table.release(); // Philosopher finishes eating
    }
}

int main(int argc, char* argv[]) {
    srand(time(nullptr));

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

    mutex mo;

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.emplace_back(philosopher, i,
                                  ref(forks[i]),
                                  ref(forks[(i + 1) % numPhilosophers]),
                                  ref(table),
                                  ref(mo));
    }

    for (auto &t : philosophers) {
        t.join();
    }

    return 0;
}

#include <thread>
#include <atomic>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Futex {
  private:
    std::atomic<std::thread::id> locking_thread_id;
  public:
    Futex() : locking_thread_id(std::thread::id()) {}
    void lock() {
        std::thread::id current_thread_id = std::this_thread::get_id();
        if (locking_thread_id.compare_exchange_strong(
            current_thread_id,
            current_thread_id,
            std::memory_order_release,
            std::memory_order_relaxed)) {
            throw "locking twice on the same thread";
        }
        std::thread::id default_thread_id = std::thread::id();
        while(!locking_thread_id.compare_exchange_weak(
            default_thread_id, 
            current_thread_id,
            std::memory_order_release,
            std::memory_order_relaxed));
    }
    void unlock() {
        std::thread::id current_thread_id = std::this_thread::get_id();
        if (!locking_thread_id.compare_exchange_strong(
            current_thread_id,
            std::thread::id(),
            std::memory_order_release,
            std::memory_order_relaxed)) {
            throw "unlocking non-locked or locked by other";
        }
    }
};

vector<int> own_work;
int total = 0;
int desired = 1000;

void inc(mutex& futex, int i) {
    bool desired_is_reached = false;
    while(!desired_is_reached) {
        futex.lock();
        if (total < desired) {
            ++total;
            ++own_work[i];
        } else {
            desired_is_reached = true;
        }
        futex.unlock();
    }
}

int  main() {
    int Nthreads = 5;
    
    
   
    std::vector<std::thread> t;
    mutex futex;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    for (int i = 0; i < Nthreads; ++i) {
        own_work.push_back(0);
        t.push_back(thread(inc, 
            ref(futex), i));
    }
    for (int i = 0; i < t.size(); ++i)
        t[i].join();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    long long ans_time = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << " " << setw(6) 
         << ans_time / 1000 << " " << setw(3) << ans_time % 1000
         << endl;
    return 0;
}
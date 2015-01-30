#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

int get_random_number_in_range(int start, int end)
{
    random_device rd;
    default_random_engine e1(rd());
    uniform_int_distribution<> uniform_dist(start, end);
    return uniform_dist(e1);
}

void sleep_for_random_time()
{
    auto msecs = get_random_number_in_range(1, 20);
    this_thread::sleep_for(chrono::milliseconds(msecs));
}

class semaphore
{
public:
    explicit semaphore(size_t count = 0):
        count_(count) {}
    
    semaphore(const semaphore&) = delete;
    semaphore& operator=(const semaphore&) = delete;

    void post()
    {
        {
            lock_guard<mutex> _(mutex_);
            ++count_;
        }
        cv_.notify_one();
    }

    void wait()
    {
        unique_lock<mutex> _(mutex_);
        cv_.wait(_, 
                [this] ()
                {
                    return count_ > 0;
                });
        --count_;
    }
private:
    size_t count_;
    mutex mutex_;
    condition_variable cv_;
};
semaphore sem;


void consumer(int i)
{
    sleep_for_random_time();
    sem.wait();
    ostringstream os;
    os << "consumer " << i << endl;
    cout << os.str() << flush;
}

void producer()
{
    for (int i = 0 ; i < 10; ++i) {
        sleep_for_random_time();
        ostringstream os;
        os << "notifying a thread" << endl;
        cout << os.str() << flush;
        sem.post();
    }
}

int main()
{
    for (int i = 0 ; i < 10; ++i) {
        auto cons = thread(consumer, i);
        cons.detach();
    }
    auto prod = thread(producer);
    prod.join();
}

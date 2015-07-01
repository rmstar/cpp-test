#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <condition_variable>
#include <thread>
#include <deque>
#include <vector>
#include <functional>

#include "utils.h"

class ThreadPool
{
public:

    ThreadPool(int nthreads = 2): nthreads_(nthreads), do_stop_(false)
    {
        for (int i = 0; i < nthreads_; ++i) {
            threads_.emplace_back([this] (int i)
                                  {
                                      worker(i);
                                  },
                                  i);
        }
    }

    void worker(int i)
    {
        while (1) {
            utils::sleep_for_random_time();
            std::unique_lock<std::mutex> _(mutex_);
            cv_.wait(_, 
                    [this] ()
                    {
                        return list_.size() > 0 || do_stop_;
                    });
            if (do_stop_) {
                break;
            }
            auto var = list_.front();
            list_.pop_front();
            std::cout << "worker " << i << ": ";
            var();
        }
        std::cout << "exiting worker " << i << "\n";
    }

    void enqueue(std::function<void ()> f)
    {
        {
            std::lock_guard<std::mutex> _(mutex_);
            list_.push_back(std::move(f));
        }
        cv_.notify_one();
    }

    void stop()
    {
        do_stop_ = true;
        cv_.notify_all();
        for (auto &t: threads_) {
            t.join();
        }
    }

private:
    int nthreads_;
    std::atomic_bool do_stop_;
    std::vector<std::thread> threads_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::deque<std::function<void ()>> list_;
};

int main()
{
    ThreadPool pool;
    for (int i = 0 ; i < 10; ++i) {
        utils::sleep_for_random_time();
        std::cout << "enqueueing " << i << "\n";
        pool.enqueue([i] ()
                     {
                         std::cout << i*i << "\n";
                     });
    }
    pool.stop();
}

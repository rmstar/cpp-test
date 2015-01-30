#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>

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
            std::lock_guard<std::mutex> _(mutex_);
            ++count_;
        }
        cv_.notify_one();
    }

    void wait()
    {
        std::unique_lock<std::mutex> _(mutex_);
        cv_.wait(_, 
                [this] ()
                {
                    return count_ > 0;
                });
        --count_;
    }
private:
    size_t count_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

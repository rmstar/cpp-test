#pragma once
#include <random>
#include <thread>
#include <chrono>

namespace utils {
    int get_random_number_in_range(int start, int end)
    {
        std::random_device rd;
        std::default_random_engine e1(rd());
        std::uniform_int_distribution<> uniform_dist(start, end);
        return uniform_dist(e1);
    }

    void sleep_for_random_time()
    {
        auto msecs = get_random_number_in_range(1, 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(msecs));
    }
}

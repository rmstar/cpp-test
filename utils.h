#pragma once
#include <random>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

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

    std::vector<std::string> split_string(const std::string &str,
                                          const std::string &delims)
    {
        std::vector<std::string> strs;
        boost::split(strs, str, boost::is_any_of(delims));
        return strs;
    }

    template <typename F, typename ...Args>
    auto get_execution_time(F func, Args... args)
    {
        typedef std::chrono::high_resolution_clock Clock;
        typedef std::chrono::duration<double, std::nano> ns;
        Clock::time_point t0 = Clock::now();

        func(args...);
        Clock::time_point t1 = Clock::now();
        ns s0 = t1 - t0;
        return s0.count();
    }
}

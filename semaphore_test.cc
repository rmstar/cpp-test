#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "utils.h"
#include "semaphore.h"

semaphore sem;

void consumer(int i)
{
    utils::sleep_for_random_time();
    sem.wait();
    std::ostringstream os;
    os << "consumer " << i << std::endl;
    std::cout << os.str() << std::flush;
}

void producer()
{
    for (int i = 0 ; i < 10; ++i) {
        utils::sleep_for_random_time();
        std::ostringstream os;
        os << "notifying a thread" << std::endl;
        std::cout << os.str() << std::flush;
        sem.post();
    }
}

int main()
{
    for (int i = 0 ; i < 10; ++i) {
        auto cons = std::thread(consumer, i);
        cons.detach();
    }
    auto prod = std::thread(producer);
    prod.join();
}

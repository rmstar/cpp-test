#include <iostream>
#include <thread>
#include <numeric>
#include <vector>
#include <chrono>

using namespace std;


int parallel_sum(const vector<int> &v, int num_threads)
{

   vector<thread> threads(num_threads);
   vector<int> results(num_threads, 0);

   auto start = v.cbegin();
   const auto size = v.size();
   const auto chunk_size = size/num_threads;
   auto remainder = chunk_size + (size % num_threads);

   for(int i = 0; i < num_threads; ++i) {
       auto end = start;
       if ( i != num_threads - 1) {
           advance(end, chunk_size);
       } else {
           advance(end, remainder);
       }
       threads[i] = thread(
               [] (vector<int>::const_iterator start,
                   vector<int>::const_iterator end,
                   int &result)
               {
                   result = accumulate(start, end, 0);
               },
               start, end, ref(results[i]));
       start = end;
   }

   for (int i = 0; i < num_threads; ++i) {
       threads[i].join();
   }
   return accumulate(results.begin(), results.end(), 0);
}

int main()
{
   vector<int> v(100000, 1);

   typedef chrono::high_resolution_clock Clock;
   typedef chrono::microseconds microseconds;

   {
       auto num_threads = thread::hardware_concurrency();
       if (!num_threads) {
           cout << "Can't get the number of concurrent threads, setting it to 1\n";
           num_threads = 1;
       }

       for (int i = 1; i <= num_threads;++i) {
           Clock::time_point t0 = Clock::now();
           cout << "sum is " << parallel_sum(v, num_threads) << endl;
           Clock::time_point t1 = Clock::now();
           auto ms = chrono::duration_cast<microseconds>(t1-t0);
           cout << "parallel sum time with " << i << " threads: " << ms.count() << endl;
       }
   }

   {
       Clock::time_point t0 = Clock::now();
       cout << "sum is " << accumulate(v.begin(), v.end(), 0) << endl;
       Clock::time_point t1 = Clock::now();
       auto ms = chrono::duration_cast<microseconds>(t1-t0);
       cout << "single-threaded sum time: " << ms.count() << endl;
   }
}

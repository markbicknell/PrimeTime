#include "cpu_generator.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <future>

bool is_prime(uint64_t number_to_test, const std::vector<uint64_t>& input_primes)
{
    // If any of the existing primes are a factor, then this number is not a prime.
    // Note that we stop when we cross the square root of the number, as we would have found
    // a factor by then if there was one
    uint64_t square_root = (uint64_t)floor(sqrt((double)number_to_test));
    bool found_factor = false;
    for (size_t prime_index = 0; prime_index < input_primes.size() &&
        input_primes[prime_index] <= square_root; prime_index++)
    {
        if (number_to_test % input_primes[prime_index] == 0)
        {
            // Found a factor, so number_to_test is not a prime.
            return false;
        }
    }
    // Found no factors, so number_to_test is prime.
    return true;
}


// Finds all the prime numbers in a given range, from 'start_number' to 'end_number' inclusive
//  'input_primes' should include all the factors that need to be tested for the requested range.
bool find_primes_in_range(uint64_t start_number, uint64_t end_number,
                           const std::vector<uint64_t>& input_primes,
                           std::vector<uint64_t>& results)
{
    uint64_t number_to_test = start_number;
    while (number_to_test <= end_number)
    {
        if (is_prime(number_to_test, input_primes))
        {
            results.push_back(number_to_test);
        }

        number_to_test++;
    }

    return true;
}

std::vector<uint64_t> generate_primes(size_t num_primes_to_generate)
{
    std::vector<uint64_t> primes;
    uint64_t number_to_test = 2; // 1 is not a prime so we start with 2
    
    while (primes.size() < num_primes_to_generate && primes.size() < 1000)
    {
        if (is_prime(number_to_test, primes))
        {
            primes.push_back(number_to_test);
        }
        number_to_test++;
    }

    while (primes.size() < num_primes_to_generate)
    {
        // Now we have a "seed" set of 1000 primes, let's generate the rest of the requested
        // primes in slices across several CPU threads
        constexpr size_t num_threads = 8;
        std::vector<uint64_t> thread_prime_results[num_threads];
        std::future<bool> workload_complete[num_threads];
        constexpr size_t slice_size = 1600000;
        uint64_t slice_end = number_to_test + slice_size - 1;
        // Quick check that the slice is not too big
        if ((uint64_t)floor(sqrt((double)slice_end) > primes.back()))
        {
            std::cout << "ERROR: slice goes beyond the square of the largest current prime! Aborting" << std::endl;
            return primes;
        }

        // Distribute the slice among 'num_threads' workers
        for (size_t worker_idx = 0; worker_idx < num_threads; worker_idx++)
        {
            constexpr size_t workload = slice_size / num_threads;
            uint64_t workload_start = number_to_test;
            uint64_t workload_end = number_to_test + workload - 1;

            // Note: we should probably get the results in the return future instead of this std::ref mess
            workload_complete[worker_idx] = std::async(std::launch::async,
                find_primes_in_range, workload_start, workload_end, primes, std::ref(thread_prime_results[worker_idx]));

            number_to_test = workload_end + 1;
        }
        // Wait for the async tasks to complete and add the new primes to the list
        for (size_t worker_idx = 0; worker_idx < num_threads; worker_idx++)
        {
            workload_complete[worker_idx].wait();
            primes.insert(primes.end(), thread_prime_results[worker_idx].begin(), thread_prime_results[worker_idx].end());
        }
    }

    // Snip off any extra primes we generated.
    primes.resize(num_primes_to_generate);

    return primes;
}
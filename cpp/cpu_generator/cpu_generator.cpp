#include "cpu_generator.h"
#include <math.h>

std::vector<uint64_t> generate_primes(size_t num_primes_to_generate) {
    std::vector<uint64_t> primes;

    // 1 is not a prime so we start with 2
    uint64_t number_to_test = 2;

    while (primes.size() < num_primes_to_generate) {
        // If any of the existing primes are a factor, then this number is not a prime.
        // Note that we stop when we cross the square root of the number, as we would have found
        // a factor by then if there was one
        uint64_t square_root = (uint64_t)floor(sqrt((double)number_to_test));
        bool found_factor = false;
        for (size_t prime_index = 0; prime_index < primes.size() &&
            primes[prime_index] <= square_root; prime_index++) {
            if (number_to_test % primes[prime_index] == 0) {
                found_factor = true;
                break;
            }
        }

        if (!found_factor) {
            primes.push_back(number_to_test);
        }

        number_to_test++;
    }

    return primes;
}
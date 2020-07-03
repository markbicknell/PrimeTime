#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>

// Remove the x to print out the results (this can be very slow for large numbers of primes).
#define PRINT_RESULTSx

// Convert an int such as 1000000 to a string with thousands separators e.g. "1,000,000"
template<typename T>
std::string int_to_grouped_digits(T integer) {
    std::ostringstream oss;
    oss.imbue(std::locale(""));
    oss << integer;
    return oss.str();
}

int main(int argc, const char** argv) {
    if(argc != 2) {
        std::cout << "Usage: primetime <num_primes_to_generate>";
        return 0;
    }

    size_t num_primes_to_compute = (size_t)std::stoi(argv[1]);
    std::cout << "Generating prime numbers!\n";
    std::vector<int64_t> primes;

    // 1 is not a prime so we start with 2
    int64_t number_to_test = 2;

    auto start = std::chrono::system_clock::now();
    while (primes.size() < num_primes_to_compute) {
        // If any of the existing primes are a factor, then this number is not a prime.
        // Note that we stop when we cross the square root of the number, as we would have found
        // a factor by then if there was one
        int64_t square_root = (int64_t)floor(sqrt(number_to_test));
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
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> calculation_time = end - start;

#ifdef PRINT_RESULTS
    for (auto prime : primes) {
        std::cout << std::to_string(prime) << "\n";
    }
#endif // PRINT_RESULTS

    std::cout << "Generated " << int_to_grouped_digits(num_primes_to_compute) << " primes in "
        << calculation_time.count() << " seconds" << std::endl;

    std::cout << "Smallest " << primes[0] << " largest " 
        << int_to_grouped_digits(primes[primes.size() - 1]) << std::endl;
    return 0;
}

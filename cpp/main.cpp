#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>

#include "cpu_generator/cpu_generator.h"

// Remove the x to print out the results (this can be very slow for large numbers of primes).
#define PRINT_RESULTSx

// Convert an int such as 1000000 to a string with thousands separators e.g. "1,000,000"
template<typename T>
std::string int_to_grouped_digits(T integer)
{
    std::ostringstream oss;
    oss.imbue(std::locale(""));
    oss << integer;
    return oss.str();
}


int main(int argc, const char** argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: primetime <num_primes_to_generate>";
        return 0;
    }

    size_t num_primes_to_compute = (size_t)std::stoi(argv[1]);
    std::cout << "Generating prime numbers!\n";
    auto start = std::chrono::system_clock::now();
    std::vector<uint64_t> primes = generate_primes(num_primes_to_compute);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> calculation_time = end - start;

#ifdef PRINT_RESULTS
    for (auto prime : primes)
    {
        std::cout << std::to_string(prime) << "\n";
    }
#endif // PRINT_RESULTS

    std::cout << "Generated " << int_to_grouped_digits(num_primes_to_compute) << " primes in "
        << calculation_time.count() << " seconds" << std::endl;

    std::cout << "Smallest " << primes[0] << " largest " 
        << int_to_grouped_digits(primes[primes.size() - 1]) << std::endl;
    return 0;
}

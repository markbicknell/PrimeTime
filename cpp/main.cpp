#include <iostream>
#include <vector>
#include <string>
#include <chrono>

int main(int argc, const char** argv){
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
        // If any of the existing primes are a factor, then this number is not a prime
        bool found_factor = false;
        for (auto existing_prime : primes) {
            if (number_to_test % existing_prime == 0) {
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

    for (auto prime : primes) {
        std::cout << std::to_string(prime) << "\n";
    }

    std::cout << "Generated " << num_primes_to_compute << " primes in " << calculation_time.count() << " seconds" << std::endl;
    
    return 0;
}

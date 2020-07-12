// This tells Catch to provide a main()
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "cpu_generator.h"

TEST_CASE( "Zero primes are generated", "[primetime]" ) {
    auto primes = generate_primes(0);
    REQUIRE(primes.size() == 0);
}

TEST_CASE("One prime is generated", "[primetime]") {
    auto primes = generate_primes(1);
    REQUIRE(primes.size() == 1);
    REQUIRE(primes[0] == 2);
}

TEST_CASE("One hundred primes are generated correctly", "[primetime]") {
    std::vector<uint64_t> expected_primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541 };
    auto primes = generate_primes(100);
    REQUIRE(primes.size() == 100);
    for (size_t index = 0; index < 100; index++) {
        REQUIRE(primes[index] == expected_primes[index]);
    }
}

TEST_CASE("One hundred thousand primes are generated correctly", "[primetime]") {
    auto primes = generate_primes(100000);
    REQUIRE(primes.size() == 100000);
    REQUIRE(primes[99999] == 1299709);
}

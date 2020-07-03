# PrimeTime
Prime number generation exercise.

## Building
The C++ version of primetime can be build via cmake:

    cd cpp
    mkdir build
    cd build
    cmake ..
    cmake --build .
    
## Running
    Usage: primetime <num_primes_to_generate>
E.g:

    > primetime 1000000
    Generating prime numbers!
    Generated 1,000,000 primes in 4.30171 seconds
    Smallest 2 largest 15,485,863

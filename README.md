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

    >primetime 4
    Generating prime numbers!
    2
    3
    5
    7
    Generated 4 primes in 3.2e-06 seconds
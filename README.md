# PrimeTime
Prime number generation exercise.

<p align="left">
  <a href="https://github.com/markbicknell/PrimeTime"><img alt="CI Status" src="https://github.com/markbicknell/PrimeTime/workflows/CI/badge.svg"></a>
</p>

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

## Testing
PrimeTime uses [Catch2](https://github.com/catchorg/Catch2) for unit tests.
From the cmake build directory simply run:

    ctest
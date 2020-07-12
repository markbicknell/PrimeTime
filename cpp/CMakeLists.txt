cmake_minimum_required(VERSION 3.10)

project(PrimeTime)

# CPU generation library
add_library (cpu_generator
             cpu_generator/cpu_generator.cpp
             cpu_generator/cpu_generator.h)
target_include_directories (cpu_generator PUBLIC cpu_generator)

# PrimeTime executable
add_executable(primetime main.cpp)
target_link_libraries (primetime LINK_PUBLIC cpu_generator)

# Catch2 unit tests
add_executable(unit_test test/unit_tests.cpp)
target_link_libraries (unit_test LINK_PUBLIC cpu_generator)
target_include_directories (unit_test PUBLIC third_party/catch2)

# Set up CTest
enable_testing()
add_test(unit_tests unit_test)

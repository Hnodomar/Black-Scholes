cmake_minimum_required(VERSION 3.16)
project(BlackScholesPricing)

set(CMAKE_CXX_STANDARD 17)

add_library(pricingmath
    src/mathlib/pricingmath.cpp
)

target_include_directories(pricingmath PUBLIC
    include/mathlib
)

enable_testing()
add_subdirectory(tests)

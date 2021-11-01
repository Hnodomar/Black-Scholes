cmake_minimum_required(VERSION 3.16)
project(BlackScholesPricing)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -march=native -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB bs_model_src
    src/BlackScholesModel.cpp
)

add_library(pricingmath
    src/mathlib/pricingmath.cpp
)

target_include_directories(pricingmath PUBLIC
    include/mathlib
)

enable_testing()
add_subdirectory(tests)

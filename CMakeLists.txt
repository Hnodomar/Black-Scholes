cmake_minimum_required(VERSION 3.16)
project(BlackScholesPricing)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -march=native -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB bs_model_src
    "src/pricing/BlackScholesModel.cpp"
    "src/options/calloption.cpp"
    "src/options/putoption.cpp"
    "src/pricing/montecarlopricer.cpp"
)

file(GLOB bs_model_inc
    "include/options/"
    "include/pricing/"
)

add_library(pricingmath
    "src/mathlib/pricingmath.cpp"
)

target_include_directories(pricingmath PUBLIC
    include/mathlib
)

enable_testing()
add_subdirectory(tests)

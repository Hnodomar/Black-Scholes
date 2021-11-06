cmake_minimum_required(VERSION 3.16)
project(BlackScholesPricing)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -march=native -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB bs_model_src
    "src/BlackScholesModel.cpp"
    "src/options/calloption.cpp"
    "src/options/putoption.cpp"
    "src/montecarlopricer.cpp"
)

file(GLOB bs_model_inc
    "include/"
    "include/options/"
)

add_library(pricingmath
    "src/mathlib/pricingmath.cpp"
)

target_include_directories(pricingmath PUBLIC
    include/mathlib
)

enable_testing()
add_subdirectory(tests)

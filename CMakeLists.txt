cmake_minimum_required(VERSION 3.16)
project(BlackScholesPricing)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -march=native -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(src_dir "${CMAKE_SOURCE_DIR}/src")
set(inc_dir "${CMAKE_SOURCE_DIR}/include")

file(GLOB bs_model_src CONFIGURE_DEPENDS
    "${src_dir}/pricing/*.cpp"
    "${src_dir}/options/*.cpp"
    "${src_dir}/hedging/*.cpp"
)

file(GLOB bs_model_inc CONFIGURE_DEPENDS
    "${inc_dir}/options"
    "${inc_dir}/pricing"
    "${inc_dir}/hedging"
)

add_library(optionspricing
    ${bs_model_src}
)

target_include_directories(optionspricing PUBLIC
    ${bs_model_inc}
    ${inc_dir}/mathlib
)

add_library(pricingmath
    "${src_dir}/mathlib/pricingmath.cpp"
)

target_include_directories(pricingmath PUBLIC
    ${inc_dir}/mathlib
)

enable_testing()
add_subdirectory(tests)

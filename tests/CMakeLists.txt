find_package(Catch2 REQUIRED)

add_executable(unit_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.cpp
)
target_link_libraries(unit_tests
    Catch2::Catch2
    pricingmath
)
target_include_directories(unit_tests PUBLIC
    include/mathlib
    include/
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

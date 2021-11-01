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

add_executable(visual_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/visual_tests.cpp
    ${bs_model_src}
)   
target_link_libraries(visual_tests PUBLIC
    pricingmath
)
target_include_directories(visual_tests PUBLIC
    ../include
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

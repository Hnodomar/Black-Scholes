find_package(Catch2 REQUIRED)

add_executable(unit_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.cpp
)
target_link_libraries(unit_tests
    Catch2::Catch2
    pricingmath
    optionspricing
)
target_include_directories(unit_tests PUBLIC
    ${bs_model_inc}
)

add_executable(visual_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/visual_tests.cpp
)   
target_link_libraries(visual_tests PUBLIC
    pricingmath
    optionspricing
)
target_include_directories(visual_tests PUBLIC
    ${bs_model_inc}
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

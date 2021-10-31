#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <iostream>

#include "pricingmath.hpp"

TEST_CASE("PricingMath Functionality") {
    using namespace PricingMath;
    std::vector<double> test_vector{1, 5, 3, 8, 7};
    SECTION("Standard Deviation") {
        REQUIRE(populationStandardDeviation(test_vector) == Approx(2.56125).epsilon(1e-3));
        REQUIRE(sampleStandardDeviation(test_vector) == Approx(2.35797).epsilon(1e-3));
    }
    SECTION("Vector Mean") {
        REQUIRE(vectorMean(test_vector) == 4.8);
    }
}

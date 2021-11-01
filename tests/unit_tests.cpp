#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <iostream>

#include "pricingmath.hpp"

TEST_CASE("PricingMath Functionality") {
    using namespace PricingMath;
    SECTION("Standard Deviation") {
        const std::vector<double> test_vector{1, 5, 3, 9, 7};
        REQUIRE(populationStandardDeviation(test_vector) == Approx(2.8284).epsilon(1e-3));
        REQUIRE(sampleStandardDeviation(test_vector) == Approx(3.1623).epsilon(1e-3));
    }
    SECTION("Vector Mean") {
        const std::vector<double> test_vector{1, 5, 3, 9, 7};
        REQUIRE(vectorMean(test_vector) == 5.0);
    }
    SECTION("Linear Sequence Generation") {
        const std::vector<double> lin_spaced_vect(createLinearSequence(1.0, 10.0, 4));
        REQUIRE(lin_spaced_vect[0] == 1.0);
        REQUIRE(lin_spaced_vect[1] == 4.0);
        REQUIRE(lin_spaced_vect[2] == 7.0);
        REQUIRE(lin_spaced_vect[3] == 10.0);
    }
    SECTION("Normalised Random Number Generation") {
        const std::vector<double> test_vector(getNRandomNumbers(10000));
        REQUIRE(test_vector.size() == 10000);
        REQUIRE(vectorMean(test_vector) == Approx(0.0).margin(0.1));
        REQUIRE(sampleStandardDeviation(test_vector) == Approx(1.0).epsilon(1e-1));
    }
    SECTION("Normal CDF") {
        REQUIRE(normCDF(1.96) == Approx(0.975).margin(1e-3).epsilon(0));
    }
    SECTION("Normal Inversion Calculation") {
        REQUIRE(normInverse(0.975) == Approx(1.96).margin(1e-2));
    }
}

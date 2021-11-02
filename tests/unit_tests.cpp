#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <iostream>

#include "pricingmath.hpp"
#include "calloption.hpp"
#include "BlackScholesModel.hpp"
#include "montecarlopricer.hpp"

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

TEST_CASE("Option Pricing") {
    using namespace OptionPricing;
    SECTION("Call Option Price") {
        const CallOption call(105.0, 2.0);
        const BlackScholesModel bsm(0.0, 100.0, 0.1, 0.05, 1.0);
        REQUIRE(call.price(bsm) == Approx(4.046).margin(1e-2));
    }
    SECTION("Monte Carlo Price") {
        const CallOption call(110.0, 2.0);
        const BlackScholesModel bsm(0.1, 100.0, 0.1, 0.05, 1.0);
        const MonteCarloPricer mcp(10000);
        const double price = mcp.price(call, bsm);
        const double expected = call.price(bsm);
        REQUIRE(price == Approx(expected).margin(1e-1));
    }
}

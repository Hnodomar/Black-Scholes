#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <iostream>

#include "pricingmath.hpp"
#include "calloption.hpp"
#include "putoption.hpp"
#include "BlackScholesModel.hpp"
#include "montecarlopricer.hpp"
#include "portfolio.hpp"

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
        const CallOption call(2.0, 105.0);
        const BlackScholesModel bsm(0.0, 100.0, 0.1, 0.05, 1.0);
        REQUIRE(call.price(bsm) == Approx(4.046).margin(1e-2));
    }
    SECTION("Put Option Price") {
        const PutOption put(2.0, 105.0);
        const BlackScholesModel bsm(0.0, 100.0, 0.1, 0.05, 1.0);
        const double price = put.price(bsm);
        REQUIRE(price == Approx(3.925).margin(1e-2));
    }
    SECTION("Monte Carlo Price") {
        const CallOption call(2.0, 110.0);
        const BlackScholesModel bsm(0.1, 100.0, 0.1, 0.05, 1.0);
        const MonteCarloPricer mcp(10000);
        const double price = mcp.price(call, bsm);
        const double expected = call.price(bsm);
        REQUIRE(price == Approx(expected).margin(1e-1));
    }
}

TEST_CASE("Portfolio Functionality") {
    using namespace OptionPricing;
    using PPtr = std::shared_ptr<Portfolio>;
    using CallPtr = std::shared_ptr<CallOption>;
    using PutPtr = std::shared_ptr<PutOption>;
    SECTION("Single Security") {
        PPtr portfolio(Portfolio::getInstance());
        CallPtr call(std::make_shared<CallOption>(1.0, 110));
        portfolio->add(call, 100);
        const BlackScholesModel bsm(0, 100, 0.1, 0, 0);
        const double unit_price = call->price(bsm);
        const double portfolio_price = portfolio->price(bsm);
        REQUIRE(100.0 * unit_price == Approx(portfolio_price).margin(1e-4));
    }
    SECTION("Put Call Parity") {
        PPtr portfolio(Portfolio::getInstance());
        CallPtr call(std::make_shared<CallOption>(1.0, 110));
        PutPtr put(std::make_shared<PutOption>(1.0, 110));
        portfolio->add(call, 100);
        portfolio->add(put, -100);
        BlackScholesModel bsm(0, 100, 0.1, 0, 0);
        const double expected = bsm.getStockPrice() - call->getStrike();
        const double portfolio_price = portfolio->price(bsm);
        REQUIRE(100.0 * expected == Approx(portfolio_price).margin(1e-4));
    }
}

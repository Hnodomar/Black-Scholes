#include "putoption.hpp"

using namespace OptionPricing;

PutOption::PutOption(const double maturity, const double strike)
    : ContinuousTimeOption(maturity, strike)
{}

double PutOption::price(const BlackScholesModel& bsm) const {
    const double S = bsm.getStockPrice();
    const double K = strike_;
    const double sigma = bsm.getVolatility();
    const double r = bsm.getRiskFreeRate();
    const double T = maturity_ - bsm.getDate();
    const double numerator = log(S / K) + (r + sigma * sigma * 0.5) * T;
    const double denominator = sigma * sqrt(T);
    const double d1 = numerator / denominator;
    const double d2 = d1 - denominator;
    return -S * PricingMath::normCDF(-d1) + exp(-r * T) * K * PricingMath::normCDF(-d2);
}

double PutOption::payoff(const double price_at_maturity) const {
    return std::max(strike_ - price_at_maturity, 0.0);
}

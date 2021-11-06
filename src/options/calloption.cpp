#include "calloption.hpp"

using namespace OptionPricing;

CallOption::CallOption(const double strike, const double maturity)
    : strike_(strike), maturity_(maturity)
{}

double CallOption::payoff(const double price_at_maturity) const {
    return std::max(price_at_maturity - strike_, 0.0);
}
// https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model
double CallOption::price(const BlackScholesModel& bsm) const {
    const double S = bsm.getStockPrice();
    const double K = strike_;
    const double sigma = bsm.getVolatility();
    const double risk_free_rate = bsm.getRiskFreeRate();
    const double T = maturity_ - bsm.getDate();
    const double numerator = log(S/K) + (risk_free_rate + sigma*sigma*0.5)*T;
    const double denominator = sigma * sqrt(T);
    const double d1 = numerator / denominator;
    const double d2 = d1 - denominator;
    return S * PricingMath::normCDF(d1) - exp(-risk_free_rate*T) * K * PricingMath::normCDF(d2);
}

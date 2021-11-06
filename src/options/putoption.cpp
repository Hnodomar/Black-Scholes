#include "putoption.hpp"

using namespace OptionPricing;

PutOption::PutOption(const double strike, const double maturity)
    : strike_(strike), maturity_(maturity)
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

double PutOption::getMaturity() const {
    return maturity_;
}

double PutOption::payoff(const double price_at_maturity) const {
    return price_at_maturity < strike_ ? strike_ - price_at_maturity : 0.0;
}

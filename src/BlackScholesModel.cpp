#include "BlackScholesModel.hpp"
#include <iostream>

BlackScholesModel::BlackScholesModel(const double drift, const double stock_price, const double volatility, const double risk_free_rate, const double date) 
    : drift_(drift)
    , stock_price_(stock_price)
    , volatility_(volatility)
    , risk_free_rate_(risk_free_rate)
    , date_(date)
{}

std::vector<double> BlackScholesModel::generateRiskNeutralPricePath(const double to_date, const int num_steps) const {
    return generatePricePath(to_date, num_steps, risk_free_rate_);
}

std::vector<double> BlackScholesModel::generatePricePath(const double to_date, const int num_steps) const {
    return generatePricePath(to_date, num_steps, drift_);
}

std::vector<double> BlackScholesModel::generatePricePath(const double to_date, const int num_steps, const double drift) const {
    std::vector<double> path(num_steps, 0.0);
    const std::vector<double> epsilon(PricingMath::getNRandomNumbers(num_steps));
    const double dt = (to_date - date_) / num_steps;
    const double a = (drift - (volatility_ * volatility_ * 0.5)) * dt;
    const double b = volatility_ * sqrt(dt);
    double curr_logS = log(stock_price_);
    for (int i = 0; i < num_steps; ++i) {
        const double dlogS = a + (b * epsilon[i]);
        const double logS = curr_logS + dlogS;
        path[i] = exp(logS);
        curr_logS = logS;
    }
    return path;
}

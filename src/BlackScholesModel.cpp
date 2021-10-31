#include "BlackScholesModel.hpp"

BlackScholesModel::BlackScholesModel(double drift, double stock_price, double volatility, double risk_free_rate, double date) 
    : drift_(drift)
    , stock_price_(stock_price)
    , volatility_(volatility)
    , risk_free_rate_(risk_free_rate)
    , date_(date)
{}

std::vector<double> BlackScholesModel::generateRiskNeutralPricePath(double to_date, int num_steps) const {
    return generatePricePath(to_date, num_steps, risk_free_rate_);
}

std::vector<double> BlackScholesModel::generatePricePath(double to_date, int num_steps) const {
    return generatePricePath(to_date, num_steps, drift_);
}

std::vector<double> BlackScholesModel::generatePricePath(double to_date, int num_steps, double drift) const {
    std::vector<double> path(num_steps, 0.0);
    std::vector<double> epsilon(PricingMath::getNRandomNumbers(num_steps));
    double dt = (to_date - date_) / num_steps;
    double a = (drift - volatility_ * volatility_ * 0.5) * dt;
    double b = volatility_ * sqrt(dt);
    double curr_logS = log(stock_price_);
    for (int i = 0; i < num_steps; ++i) {
        double dlogS = a + b * epsilon[i];
        double logS = curr_logS + dlogS;
        path[i] = exp(logS);
        curr_logS = logS;
    }
    return path;
}

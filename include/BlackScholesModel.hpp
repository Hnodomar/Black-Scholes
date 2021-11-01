#ifndef BLACK_SCHOLES_MODEL_HPP
#define BLACK_SCHOLES_MODEL_HPP

#include <vector>
#include <cmath>

#include "pricingmath.hpp"

class BlackScholesModel {
public:
    BlackScholesModel(
        const double drift, 
        const double stock_price, 
        const double volatiltiy, 
        const double risk_free_rate, 
        const double date
    );
    std::vector<double> generatePricePath(const double to_date, const int num_steps) const;
    std::vector<double> generateRiskNeutralPricePath(const double to_date, const int num_steps) const;
private:
    const double drift_;
    const double stock_price_;
    const double volatility_;
    const double risk_free_rate_;
    const double date_;
    std::vector<double> generatePricePath(
        const double to_date,
        const int num_steps,
        const double drift
    ) const;
};

#endif

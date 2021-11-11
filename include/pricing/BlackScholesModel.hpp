#ifndef BLACK_SCHOLES_MODEL_HPP
#define BLACK_SCHOLES_MODEL_HPP

#include <vector>
#include <cmath>

#include "pricingmath.hpp"
namespace OptionPricing {
class BlackScholesModel {
public:
    BlackScholesModel(
        const double drift, 
        const double stock_price, 
        const double volatility, 
        const double risk_free_rate, 
        const double date
    );
    std::vector<double> generatePricePath(const double to_date, const int num_steps) const;
    std::vector<double> generateRiskNeutralPricePath(const double to_date, const int num_steps) const;
    double getStockPrice() const {return stock_price_;}
    double getVolatility() const {return volatility_;}
    double getRiskFreeRate() const {return risk_free_rate_;}
    double getDate() const {return date_;}
    double getDrift() const {return drift_;}
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
}
#endif

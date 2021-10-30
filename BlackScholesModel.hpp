#ifndef BLACK_SCHOLES_MODEL_HPP
#define BLACK_SCHOLES_MODEL_HPP

#include <vector>

class BlackScholesModel {
public:
    BlackScholesModel(
        double drift, 
        double stock_price, 
        double volatiltiy, 
        double risk_free_rate, 
        double date
    );
    std::vector<double> generatePricePath(double to_date, int num_steps) const;
    std::vector<double> generateRiskNeutralPricePath(double to_date, int num_steps) const;
private:
    double drift_;
    double stock_price_;
    double volatility_;
    double risk_free_rate_;
    double date_;
    std::vector<double> generatePricePath(
        double to_date,
        int num_steps,
        double drift
    ) const;
};

#endif

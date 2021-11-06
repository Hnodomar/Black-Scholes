#ifndef CALL_OPTION_HPP
#define CALL_OPTION_HPP

#include <cmath>

#include "pricingmath.hpp"
#include "BlackScholesModel.hpp"
#include "pathindependentoption.hpp"

namespace OptionPricing {
class CallOption : public PathIndependentOption {
public:
    CallOption(const double strike, const double maturity);
    double payoff(const double price_at_maturity) const override;
    double price(const BlackScholesModel& bsm) const; // https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model
    double getMaturity() const override {return maturity_;}
private:
    const double strike_;
    const double maturity_;
};
}

#endif

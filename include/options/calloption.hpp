#ifndef CALL_OPTION_HPP
#define CALL_OPTION_HPP

#include <cmath>

#include "pricingmath.hpp"
#include "BlackScholesModel.hpp"
#include "continuoustimeoption.hpp"

namespace OptionPricing {
class CallOption : public ContinuousTimeOption {
public:
    CallOption(const double maturity, const double strike);
    double payoff(const double price_at_maturity) const override;
    double price(const BlackScholesModel& bsm) const; // https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model
    bool isPathDependent() const override {return false;}
};
}

#endif

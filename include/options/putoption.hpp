#ifndef PUT_OPTION_HPP
#define PUT_OPTION_HPP

#include "BlackScholesModel.hpp"
#include "continuoustimeoption.hpp"

namespace OptionPricing {
class PutOption : public ContinuousTimeOption {
public:
    PutOption(const double maturity, const double strike);
    double payoff(const double price_at_maturity) const override;
    double price(const BlackScholesModel& bsm) const;
    bool isPathDependent() const override {return false;}
};
}

#endif

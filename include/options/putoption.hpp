#ifndef PUT_OPTION_HPP
#define PUT_OPTION_HPP

#include "BlackScholesModel.hpp"
#include "pathindependentoption.hpp"

namespace OptionPricing {
class PutOption : public PathIndependentOption {
public:
    PutOption(const double strike, const double maturity);
    double payoff(const double price_at_maturity) const override;
    double price(const BlackScholesModel& bsm) const;
    double getMaturity() const override;
private:
    const double strike_;
    const double maturity_;
};
}

#endif

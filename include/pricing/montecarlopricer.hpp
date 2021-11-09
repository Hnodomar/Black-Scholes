#ifndef MONTE_CARLO_PRICER
#define MONTE_CARLO_PRICER

#include "BlackScholesModel.hpp"
#include "continuoustimeoption.hpp"

namespace OptionPricing {
class ContinuousTimeOption;
class MonteCarloPricer {
public:
    MonteCarloPricer(const size_t num_scenarios = 10000);
    double price(const ContinuousTimeOption& option, const BlackScholesModel& bsm) const;
private:
    const size_t num_scenarios_;
};
}

#endif

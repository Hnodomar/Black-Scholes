#ifndef MONTE_CARLO_PRICER
#define MONTE_CARLO_PRICER

#include "calloption.hpp"
#include "BlackScholesModel.hpp"
namespace OptionPricing {
class MonteCarloPricer {
public:
    MonteCarloPricer(const size_t num_scenarios);
    double price(const CallOption& option, const BlackScholesModel& bsm) const;
private:
    const size_t num_scenarios_;
};
}

#endif

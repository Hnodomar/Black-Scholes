#include "continuoustimeoption.hpp"

using namespace OptionPricing;

double ContinuousTimeOption::price(const BlackScholesModel& bsm) const {
    static const MonteCarloPricer pricer;
    return pricer.price(*this, bsm);
}

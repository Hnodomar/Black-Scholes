#include "montecarlopricer.hpp"

using namespace OptionPricing;

MonteCarloPricer::MonteCarloPricer(const size_t num_scenarios)
    : num_scenarios_(num_scenarios)
{}

double MonteCarloPricer::price(const ContinuousTimeOption& call, const BlackScholesModel& bsm) const {
    double total = 0.0;
    for (size_t i = 0; i < num_scenarios_; ++i) {
        const std::vector<double> path = bsm.generateRiskNeutralPricePath(
            call.getMaturity(),
            1
        );
        const double stock_price = path.back();
        const double payoff = call.payoff(stock_price);
        total += payoff;
    }
    const double mean = total / num_scenarios_;
    const double r = bsm.getRiskFreeRate();
    const double T = call.getMaturity() - bsm.getDate();
    return exp(-r*T) * mean;
}

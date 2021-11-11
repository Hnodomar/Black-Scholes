#ifndef HEDGING_SIM_HPP
#define HEDGING_SIM_HPP

#include <memory>

#include "BlackScholesModel.hpp"
#include "calloption.hpp"

namespace OptionPricing {
class HedgingSimulator {
public:
    HedgingSimulator(
        std::shared_ptr<CallOption> to_hedge, 
        std::shared_ptr<BlackScholesModel> sim_model,
        std::shared_ptr<BlackScholesModel> price_model,
        const size_t num_steps = 10000
    );
    std::vector<double> runSimulations(size_t num_simulations) const;
private:
    double runSimulation() const;
    double chooseCharge(const double stock_price) const;
    double selectStockQuantity(
        const double date,
        const double stock_price
    ) const;
    std::shared_ptr<CallOption> to_hedge_;
    std::shared_ptr<BlackScholesModel> simulation_model_;
    std::shared_ptr<BlackScholesModel> pricing_model_;
    const size_t num_steps_;
};
}

#endif

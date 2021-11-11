#include "hedgingsim.hpp"

using namespace OptionPricing;

HedgingSimulator::HedgingSimulator(std::shared_ptr<CallOption> to_hedge, 
 std::shared_ptr<BlackScholesModel> sim_model, std::shared_ptr<BlackScholesModel> price_model,
 const size_t num_steps)
    : to_hedge_(to_hedge)
    , simulation_model_(sim_model)
    , pricing_model_(price_model)
    , num_steps_(num_steps)
{}

std::vector<double> HedgingSimulator::runSimulations(const size_t num_simulations) const {
    std::vector<double> simulations(num_simulations);
    for (size_t i = 0; i < num_simulations; ++i)
        simulations[i] = runSimulation();
    return simulations;
}

double HedgingSimulator::runSimulation() const {
    const double maturity = to_hedge_->getMaturity();
    const double initial_stock_price = simulation_model_->getStockPrice();
    const std::vector<double> price_path(
        simulation_model_->generatePricePath(
            maturity, num_steps_
        )
    );
    const double dt = maturity / num_steps_;
    const double charge = chooseCharge(initial_stock_price);
    double stock_qty = selectStockQuantity(0, initial_stock_price);
    double balance = charge - stock_qty * initial_stock_price;
    for (size_t i = 0; i < num_steps_ - 1; ++i) {
        const double balance_with_interest = balance * exp(
            simulation_model_->getRiskFreeRate() * dt
        );
        const double curr_stock_price = price_path[i];
        const double date = dt * (i + 1);
        const double new_stock_qty = selectStockQuantity(date, curr_stock_price);
        const double costs = (new_stock_qty - stock_qty) * curr_stock_price;
        balance = balance_with_interest - costs;
        stock_qty = new_stock_qty;
    }
    const double balance_with_interest = balance * exp(simulation_model_->getRiskFreeRate() * dt);
    const double curr_stock_price = price_path[num_steps_ - 1];
    const double stock_value = stock_qty * curr_stock_price;
    const double payout = to_hedge_->payoff(curr_stock_price);
    return balance_with_interest + stock_value - payout;
}

double HedgingSimulator::selectStockQuantity(const double date, const double stock_price) const {
    const BlackScholesModel pm(
      pricing_model_->getDrift(),
      stock_price,
      pricing_model_->getVolatility(),
      pricing_model_->getRiskFreeRate(),
      date
    );
    return to_hedge_->delta(std::move(pm));
}

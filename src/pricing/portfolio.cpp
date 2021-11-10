#include "portfolio.hpp"

using namespace OptionPricing;

size_t Portfolio::size() const {
    return quantities_.size(); 
}

size_t Portfolio::add(std::shared_ptr<Priceable> security, const double quantity) {
    quantities_.push_back(quantity);
    securities_.push_back(security);
    return quantities_.size();
}

double Portfolio::price(const BlackScholesModel& bsm) const {
    double ret = 0.0;
    for (size_t i = 0; i < size(); ++i)
        ret += quantities_[i] * securities_[i]->price(bsm);
    return ret;
}

void Portfolio::setQuantity(const size_t idx, const double qty) {
    quantities_[idx] = qty;
}

std::shared_ptr<Portfolio> Portfolio::getInstance() {
    return std::make_shared<Portfolio>();
}

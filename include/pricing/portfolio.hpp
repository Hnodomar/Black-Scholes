#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <memory>
#include <vector>

#include "priceable.hpp"

namespace OptionPricing {
class Portfolio : public Priceable {
public: 
    size_t size() const;
    size_t add(std::shared_ptr<Priceable> security, const double qty);
    void setQuantity(const size_t idx, const double qty);
    double price(const BlackScholesModel& bsm) const override;
    static std::shared_ptr<Portfolio> getInstance();
private:
    std::vector<double> quantities_;
    std::vector<std::shared_ptr<Priceable>> securities_;
};
}

#endif

#ifndef PRICEABLE_HPP
#define PRICEABLE_HPP

#include "BlackScholesModel.hpp"

namespace OptionPricing {
class Priceable {
public:
    virtual double price(const BlackScholesModel& model) const = 0;
};
}

#endif

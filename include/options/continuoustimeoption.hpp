#ifndef CONT_TIME_OPTION_HPP
#define CONT_TIME_OPTION_HPP

#include <vector>

#include "priceable.hpp"
#include "montecarlopricer.hpp"

namespace OptionPricing {
class MonteCarloPricer;
class ContinuousTimeOption : public Priceable {
public:
    ContinuousTimeOption(const double maturity, const double strike)
        : maturity_(maturity), strike_(strike)
    {}
    virtual ~ContinuousTimeOption() {};
    double getMaturity() const {return maturity_;}
    void setMaturity(const double maturity) {maturity_ = maturity;}
    double getStrike() const {return strike_;}
    void setStrike(const double strike) {strike_ = strike;}
    virtual double price(const BlackScholesModel& bsm) const;
    virtual double payoff(const double price_at_maturity) const = 0;
    virtual bool isPathDependent() const = 0;
protected:
    double maturity_;
    double strike_;
};
}

#endif

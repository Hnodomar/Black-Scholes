#ifndef P_INDEPENDENT_OPTION
#define P_INDEPENDENT_OPTION

namespace OptionPricing {
class PathIndependentOption {
public:
    virtual ~PathIndependentOption() {}
    virtual double payoff(const double final_stock_price) const = 0;
    virtual double getMaturity() const = 0;
};
}

#endif

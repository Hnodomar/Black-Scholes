#ifndef OPTION_PRICE_CALC
#define OPTION_PRICE_CALC

#define _USE_MATH_DEFINES
#include <cmath>

class EUOptionPriceCalc {
    public:
        EUOptionPriceCalc(
            double underlying_price, 
            double strike_price, 
            double risk_free_rate, 
            double volatility_underlying,
            double time_maturity
        );
    private:
        double callPrice() {

        }

        double putPrice() {

        }

        double getNormalStdDist(const double& x) {
            return (1.0/(pow(2*M_PI, 0.5)))*exp(-0.5*x*x);
        }

        double approxNormCDF(const double& x) {
            double k = 1.0/(1.0 + 0.)
        }

        double underlying_price_;
        double strike_price_;
        double risk_free_rate_;
        double volatility_underlying_;
        double time_maturity_;
};

#endif

#include "EUOptionPriceCalc.hpp"

EUOptionPriceCalc::EUOptionPriceCalc(
    double underlying_price, 
    double strike_price, 
    double risk_free_rate, 
    double volatility_underlying,
    double time_maturity)
    : underlying_price_(underlying_price),
      strike_price_(strike_price),
      risk_free_rate_(risk_free_rate),
      volatility_underlying_(volatility_underlying),
      time_maturity_(time_maturity) {
    
}
